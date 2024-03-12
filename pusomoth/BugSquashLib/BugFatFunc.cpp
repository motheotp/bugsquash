/**
 * @file BugFatFunc.cpp
 * @author Motheo Treasure Puso
 */
#include "pch.h"
#include "BugFatFunc.h"
#include "CodeDlg.h"
#include "Bug.h"
#include <regex>
#include <wx/graphics.h>

/// fat factor
const double FatFactor = 1.25;

/**
 * Constructor
 * @param bug pointer to bug object this code is linked to
 */
BugFatFunc::BugFatFunc(Bug* bug) : mBug(bug)
{

}

/**
 * Code Loading
 * @param node The Xml node we are loading the code from
 */
void BugFatFunc::XmlLoad(wxXmlNode *node)
{
	auto code = node->GetChildren();
	mCode = code->GetNodeContent().ToStdWstring();
	mPass = code->GetAttribute(L"pass", L"").ToStdWstring();
}

/**
 * Is edited code passed?
 * @param code code to ValidateCode
 * @return
 */
bool BugFatFunc::IsPass(std::wstring code)
{
	return std::regex_search(code, std::wregex(mPass));
}

/**
 * When fat bug get clicked
 */
void BugFatFunc::OnDClick()
{
	mBug->GetLevel()->Pause(true);
	CodeDlg dlg(mCode, this);
	dlg.ShowModal();
}

/**
 * Call back of dlg
 * @param code
 */
void BugFatFunc::DlgCallBack(std::wstring code)
{
	// If code passes, bug is clicked on
	if(IsPass(code))
	{
		mBug->Bug::OnClick();
	}
	mBug->GetLevel()->Pause(false);
}
/**
 * Draw fat bug
 * @param graphics
 */
void BugFatFunc::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	graphics->PushState();
	graphics->Translate(mBug->GetX(), mBug->GetY());
	graphics->Scale(FatFactor, FatFactor);

	// If the bug hasn't already been missed, draw bug
	if (!mBug->IsMissed())
	{
		double wid = mBug->GetBugSprite()->GetWidth();
		double hit = mBug->GetBugSprite()->GetHeight();

		graphics->DrawBitmap(*mBug->GetBugSprite(),
							 - wid / 2,
							 -hit / 2,
							 wid,
							 hit);
	}
	graphics->PopState();
}

/**
 * Hit test x,y to see if they are clicking on this bug.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return true if clicked on bug
 */
bool BugFatFunc::HitTest(double x, double y)
{
	double dX = x - mBug->GetX();
	double dY = y - mBug->GetY();
	double d = sqrt(pow(dX, 2) + pow(dY, 2));
	double angel = atan2(dY, dX);
	double realX = mBug->GetX() + (d / FatFactor) * cos(angel);
	double realY = mBug->GetY() + (d / FatFactor) * sin(angel);

	return mBug->Bug::HitTest(realX, realY);
}