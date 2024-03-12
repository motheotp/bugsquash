/**
 * @file BugRace.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "BugRace.h"
#include "RaceOrderChecker.h"
#include "Level.h"
#include "LevelManager.h"
#include <wx/graphics.h>

using namespace std;

/// Time the bug is frozen for when clicked
const double FreezeDuration = 5.0;

/// The bug sprite image
const wstring RaceConditionBugSpriteImageName = L"images/blue-cyan-bug.png";

/// Number of sprite images
const int RaceConditionBugNumSpriteImages = 5;

/// Font size for drawing the Id
const int IdFontSize = 20;

/// X Pixel offset for drawing the Id
const int IdOffsetX = 17;

/// Y Pixel offset for drawing the Id
const int IdOffsetY = 15;

/**
 * Race Condition Bug Constructor
 * @param level The level this bug belongs to
 * @param program The Program to move towards
*/
BugRace::BugRace(Level* level, shared_ptr<Program> program) :
	Bug(level, program, RaceConditionBugNumSpriteImages, RaceConditionBugSpriteImageName, RaceConditionBugSpriteImageName)
{

}

/**
 * Code Loading
 * @param node The Xml node we are loading the code from
 */
void BugRace::XmlLoad(wxXmlNode *node)
{
	Bug::XmlLoad(node);
	node->GetAttribute(L"id", L"0").ToInt(&mId);
}

/**
 * Called when the Race Condition Bug is clicked on
 */
void BugRace::OnClick()
{
	mFreeze = FreezeDuration;
}


/**
 * Update the item
 * @param elapsed elapsed time
 */
void BugRace::Update(double elapsed)
{
	mFreeze -= elapsed;
	if (mFreeze <= 0.0)
	{
		Bug::Update(elapsed);
	}
}

/**
 * Called when the bug reaches the program
 */
void BugRace::OnReachProgram()
{
	// Use visitor to check if another (lower id) race bug exists
	RaceOrderChecker visitor;
	visitor.SetReachId(mId);
	mLevel->Accept(&visitor);
	if (!visitor.GetIsNext())
	{
		mLevel->GetManager()->GetScoreboard()->IncreaseMissed();
	}
}

/**
 * Draw this bug
 * @param graphics graphics to draw on
 */
void BugRace::Draw(shared_ptr<wxGraphicsContext> graphics)
{
	if (!IsMissed())
	{
		double wid = GetBugSprite()->GetWidth();
		double hit = GetBugSprite()->GetHeight();

		graphics->PushState();

		graphics->Translate(GetX(), GetY());
		graphics->Rotate(GetRotation());
		graphics->Translate(-GetX(), -GetY());

		graphics->DrawBitmap(*GetBugSprite(),
							 int(GetX() - wid / 2),
							 int(GetY() - hit / 2),
							 wid,
							 hit);

		wxFont font(IdFontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		graphics->SetFont(font, *wxRED);
		wxString idText = wxString::Format("%d", mId);
		double textX = GetX() - IdOffsetX;
		double textY = GetY() - IdOffsetY;
		graphics->DrawText(idText, textX, textY);

		graphics->PopState();
	}
}


/**
 * Update the sprite for this bug
 * @param elapsed elapsed time
 */
void BugRace::UpdateSprite(double elapsed)
{
	shared_ptr<wxBitmap> bugBitmap;
	double wid, hit;
	bugBitmap = GetBitmap();
	hit = bugBitmap->GetHeight() / (RaceConditionBugNumSpriteImages + 1);
	wid = bugBitmap->GetWidth();

	wxMemoryDC memDC;
	memDC.SelectObject(*bugBitmap);
	SetBugSprite(make_shared<wxBitmap>(wid, hit, bugBitmap->GetDepth()));

	if (!IsMissed())
	{
		GetBugSprite()->UseAlpha();

		// Blit sprite from sprite sheet
		wxMemoryDC clippedDC;
		clippedDC.SelectObject(*GetBugSprite());
		clippedDC.Blit(0, 0, wid, hit, &memDC, 0, GetAnimation() * hit);
	}
}