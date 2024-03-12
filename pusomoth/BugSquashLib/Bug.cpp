/**
 * @file Bug.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "Bug.h"
#include "Level.h"
#include "LevelManager.h"
#include "ZombieReviver.h"
#include <wx/graphics.h>
#include <cstdlib>

using namespace std;

/// Animation duration (value/speed)
const double SpriteDuration = 3.0;

/// Distance to count a bug as missed
const double MissedDist = 10.0;

/**
 * Constructor
 * @param level The Level this item belongs to
 * @param program The Program to move towards
 * @param sprites The number of sprites for this bug
 * @param filename Filename for the image we use
 * @param filenameSplat Filename for the splat image we use
*/
Bug::Bug(Level* level, std::shared_ptr<Program> program, int sprites, const std::wstring& filename, const std::wstring& filenameSplat) : Item(level, filename)
{
	mProgram = program;
	mSpriteCount = sprites;
	mItemImageSplat = make_unique<wxImage>(filenameSplat, wxBITMAP_TYPE_ANY);
	mItemBitmapSplat = make_shared<wxBitmap>(*mItemImageSplat);
	UpdateSprite(0.0);
}

/**
 * Sets the Speed of the bug; for derived classes of bug
 *
 * @param speed the speed of the bug
*/
void Bug::SetSpeed(double speed)
{
	mSpeed = speed;
}

/**
 * Draw this bug
 * @param graphics graphics to draw on
 */
void Bug::Draw(shared_ptr<wxGraphicsContext> graphics)
{
	if (!mMissed)
	{
		double wid = mBugSprite->GetWidth();
		double hit = mBugSprite->GetHeight();

		graphics->DrawBitmap(*mBugSprite,
							 int(GetX() - wid / 2),
							 int(GetY() - hit / 2),
							 wid,
							 hit);
	}
}

/**
 * Bug Loading
 * @param node The Xml node we are loading the item from
 */
void Bug::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);
	node->GetAttribute(L"speed", L"0").ToDouble(&mSpeed);
	node->GetAttribute(L"start", L"0").ToDouble(&mStart);
}

/**
 * Update the item
 * @param elapsed elapsed time
 */
void Bug::Update(double elapsed)
{
    // Check if delay time has elapsed
    if (mElapsedDelayTime < mStart)
    {
        // Update elapsed delay time
        mElapsedDelayTime += elapsed;
        return;
    }
	// If bug has not been splat, keep updating
	if (!mSplat)
	{
		Item::Update(elapsed);

		mAnimationChange += elapsed;
		if (mAnimationChange >= SpriteDuration / mSpeed)
		{
			mAnimation++;
			if (mAnimation == mSpriteCount)
			{
				mAnimation = 0;
			}
			UpdateSprite(elapsed);
			mAnimationChange = 0;
		}

		// Update Rotation
		mRotation = atan2(mProgram->GetY() - GetY(), mProgram->GetX() - GetX());

		// TODO: Temp Movement
		SetX(GetX() + elapsed * mSpeed * cos(mRotation));
		SetY(GetY() + elapsed * mSpeed * sin(mRotation));

		// When bug reaches program (within 5 pixels)
		if (abs(mProgram->GetY() - GetY()) < MissedDist && abs(mProgram->GetX() - GetX()) < MissedDist)
		{
			if(!mMissed)
			{
				OnReachProgram();
			}
			mMissed = true;
		}

	}
	else
	{
		mAnimation = 0;
		UpdateSprite(elapsed);
	}

}
/**
 * Called when the bug reaches the program
 */
void Bug::OnReachProgram()
{
	mLevel->GetManager()->GetScoreboard()->IncreaseMissed();
}


/**
 * Update the sprite for this bug
 * @param elapsed elapsed time
 */
void Bug::UpdateSprite(double elapsed)
{
	shared_ptr<wxBitmap> bugBitmap;
	double wid, hit;
	if (!mSplat)
	{
		bugBitmap = GetBitmap();
		hit = bugBitmap->GetHeight() / (mSpriteCount + 1);
	}
	else
	{
		bugBitmap = GetBitmapSplat();
		hit = bugBitmap->GetHeight();
	}

	wid = bugBitmap->GetWidth();

	wxMemoryDC memDC;
	memDC.SelectObject(*bugBitmap);

	mBugSprite = make_shared<wxBitmap>(wid, hit, bugBitmap->GetDepth());

	if (!mMissed)
	{
		mBugSprite->UseAlpha();

		wxMemoryDC clippedDC;
		clippedDC.SelectObject(*mBugSprite);
		if (!mSplat)
		{
			clippedDC.Blit(0, 0, wid, hit, &memDC, 0, mAnimation * hit);
		}
		else
		{
			clippedDC.Blit(0, 0, wid, hit, &memDC, 0, 0);
		}

		// Rotate the final sprite by -mRotation radians
		wxImage image = mBugSprite->ConvertToImage();
		image = image.Rotate(-mRotation, wxPoint(wid / 2, hit / 2));
		mBugSprite = make_shared<wxBitmap>(image);
	}

}


/**
 * Called when Bug is clicked on
 */
void Bug::OnClick()
{
	// If not already splat and not already missed, increase fixed bugs count on scoreboard

	// Sets bug to splat and speed to zero

	if (mMissed || mSplat)
	{
		return;
	}

	// Revive zombie bugs, fired before mSplat is updated
	ZombieReviver visitor;
	mLevel->Accept(&visitor);

	AddScore();
	mSplat = true;
}

/**
 * Hit test x,y to see if they are clicking on this bug.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return true if clicked on bug
 */
bool Bug::HitTest(double x, double y)
{
	if(mMissed || mSplat)
		return false;
	double wid = mBugSprite->GetWidth();
	double hit = mBugSprite->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to the image top corner
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	// If the location is transparent, we are not in the drawn
	// part of the image
	return !mBugSprite->ConvertToImage().IsTransparent((int)testX, (int)testY);
}

/**
 * Add score
 */
void Bug::AddScore()
{
	mLevel->GetManager()->GetScoreboard()->IncreaseFixed();
}
