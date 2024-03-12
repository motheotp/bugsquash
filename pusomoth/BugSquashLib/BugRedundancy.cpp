/**
 * @file BugRedundancy.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "BugRedundancy.h"
#include "Level.h"
#include "LevelManager.h"
#include <wx/graphics.h>

using namespace std;

/// The bug base image
const std::wstring RedundancyFlyImageName = L"images/redundancy-fly-base.png";

/// The bug top image
const std::wstring RedundancyFlyTopImageName = L"images/redundancy-fly-top.png";

/// The left wing image
const std::wstring RedundancyFlyLeftWingImageName = L"images/redundancy-fly-lwing.png";

/// The right wing image
const std::wstring RedundancyFlyRightWingImageName = L"images/redundancy-fly-rwing.png";

/// The splat image
const std::wstring RedundancyFlySplatImageName = L"images/redundancy-fly-splat.png";

/// Wing flapping period in seconds
const double WingPeriod = 0.2;

/// Starting rotation angle for wings in radians
const double WingRotateStart = 0.0;

/// End rotation angle for wings in radians
const double WingRotateEnd = 1.5;

/// How many sets of wings does this bug have?
const int NumberOfSetsOfWings = 4;

/// Number of virtual pixels between each of the wing sets
const int WingSetXOffset = 12;

/// X position relative to center of bug for the first (back) wing set
const int FirstWingSetX = -36;

/// Y position relative to center of bug for the right wings. The negative
/// of this is the Y position for the left wings.
const int WingSetY = 5;

/// Number of sprite images
const int RedundancyBugNumSpriteImages = 1; // <-- Likely needs to change

/// Distance for spawned bugs
const double BugSplitDist = 200.0;

/// Split bug speed
const double SplitSpeed = 120.0;

/**
 * Redundancy Bug Constructor
 * @param level The level this bug belongs to
 * @param program The Program to move towards
*/
BugRedundancy::BugRedundancy(Level* level, shared_ptr<Program> program) :
	Bug(level, program, RedundancyBugNumSpriteImages, RedundancyFlyImageName, RedundancyFlySplatImageName)
{
	// Top Image
	mTopImage = make_unique<wxImage>(RedundancyFlyTopImageName, wxBITMAP_TYPE_ANY);
	mTopBitmap = make_unique<wxBitmap>(*mTopImage);

	// Left Wing
	mLeftWingImage = make_unique<wxImage>(RedundancyFlyLeftWingImageName, wxBITMAP_TYPE_ANY);
	mLeftWingBitmap = make_unique<wxBitmap>(*mLeftWingImage);

	// Right Wing
	mRightWingImage = make_unique<wxImage>(RedundancyFlyRightWingImageName, wxBITMAP_TYPE_ANY);
	mRightWingBitmap = make_unique<wxBitmap>(*mRightWingImage);
}

/**
 * Update the sprite for this bug
 * @param elapsed the amount of time elapsed
 */
void BugRedundancy::UpdateSprite(double elapsed)
{
	shared_ptr<wxBitmap> bugBitmap;
	if (!IsSplat())
	{
		bugBitmap = GetBitmap();
	}
	else
	{
		bugBitmap = GetBitmapSplat();
	}

	double wid = bugBitmap->GetWidth();
	double hit = bugBitmap->GetHeight();

	wxMemoryDC memDC;
	memDC.SelectObject(*bugBitmap);

	SetBugSprite(make_shared<wxBitmap>(wid, hit, bugBitmap->GetDepth()));

	// If bug hasn't already been missed, keep updating
	if (!IsMissed())
	{
		GetBugSprite()->UseAlpha();

		mTotalElapsed += elapsed;

		wxMemoryDC clippedDC;
		clippedDC.SelectObject(*GetBugSprite());

		// If bug hasn't already been splat, continue with animation
		if (!IsSplat())
		{
			clippedDC.Blit(0, 0, wid, hit, &memDC, 0, 0);

			double rotation = WingRotateStart + (WingRotateEnd - WingRotateStart) * (sin(2 * M_PI * mTotalElapsed / WingPeriod) + 1) / 2;

			for (int i = 0; i < NumberOfSetsOfWings; ++i)
			{
				int wingOffsetX = FirstWingSetX + i * WingSetXOffset;

				// Rotate left wing
				wxImage rotatedLeftWingImage = mLeftWingImage->Rotate(rotation, wxPoint(mLeftWingImage->GetWidth() / 2, mLeftWingImage->GetHeight() / 2 - WingSetY));
				wxBitmap rotatedLeftWingBitmap(rotatedLeftWingImage);

				// Rotate right wing
				wxImage rotatedRightWingImage = mRightWingImage->Rotate(-rotation, wxPoint(mRightWingImage->GetWidth() / 2, mRightWingImage->GetHeight() / 2 + WingSetY));
				wxBitmap rotatedRightWingBitmap(rotatedRightWingImage);

				// Draw rotated wings
				clippedDC.DrawBitmap(rotatedLeftWingBitmap, wingOffsetX + (mLeftWingImage->GetWidth() - rotatedLeftWingBitmap.GetWidth()) / 2, -WingSetY + (mLeftWingImage->GetHeight() - rotatedLeftWingBitmap.GetHeight()) / 2, true);
				clippedDC.DrawBitmap(rotatedRightWingBitmap, wingOffsetX + (mRightWingImage->GetWidth() - rotatedRightWingBitmap.GetWidth()) / 2, WingSetY + (mRightWingImage->GetHeight() - rotatedRightWingImage.GetHeight()) / 2, true);
			}

			// Draw the top image
			clippedDC.DrawBitmap(*mTopBitmap, 0, 0, true);
		}
		else
		{
			clippedDC.Blit(0, 0, wid, hit, &memDC, 0, 0);
		}

		// Rotate the final sprite by -mRotation radians
		wxImage image = GetBugSprite()->ConvertToImage();
		image = image.Rotate(-GetRotation(), wxPoint(wid / 2, hit / 2));
		GetBugSprite() = make_shared<wxBitmap>(image);
	}
}

/**
 * Called when RedundancyBug is clicked on
 */
void BugRedundancy::OnClick()
{
    if (mHasBeenClicked) {
        // If the bug has been clicked before, call the parent class OnClick to remove the bug
        Bug::OnClick();
    }
    else {
        // Remove the original bug from the level
		// Remove the original bug from the level
        mLevel->RemoveBug(shared_from_this());        // Set the flag to indicate that the bug has been clicked
        mHasBeenClicked = true;

        // Spawn 3 to 6 new child bugs
        int numNewBugs = rand() % 4 + 3;
        for (int i = 0; i < numNewBugs; i++) {
            auto newBug = std::make_shared<BugRedundancy>(mLevel, GetProgram());

            // Calculate random angle for child bug placement
            double angle = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
            double distance = BugSplitDist;

            // Calculate new child bug's X and Y position based on the random angle and distance
            int newX = GetX() + static_cast<int>(cos(angle) * distance);
            int newY = GetY() + static_cast<int>(sin(angle) * distance);

            newBug->SetX(newX);
            newBug->SetY(newY);
            newBug->SetSpeed(SplitSpeed);
            // Set the child bugs to have been clicked already
            newBug->mHasBeenClicked = true;
            mLevel->AddBug(newBug);
        }
    }
}

/**
 * Draw this bug
 * @param graphics graphics to draw on
 */
void BugRedundancy::Draw(shared_ptr<wxGraphicsContext> graphics)
{
	graphics->PushState();

	graphics->Translate(GetX(), GetY());
	graphics->Rotate(GetRotation());
	graphics->Translate(-GetX(), -GetY());

	Bug::Draw(graphics);

	graphics->PopState();
}