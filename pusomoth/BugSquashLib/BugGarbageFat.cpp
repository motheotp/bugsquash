/**
 * @file BugGarbageFat.cpp
 * @author Motheo Treasure Puso
 */
#include "pch.h"
#include "BugGarbageFat.h"
#include "BugFatFunc.h"
#include <wx/graphics.h>

/**
 * Constructor
 * @param level
 * @param program
 */
BugGarbageFat::BugGarbageFat(Level *level, std::shared_ptr<Program> program) : BugGarbage(level, program)
{
	mFunc = std::make_shared<BugFatFunc>(this);
}

/**
 * Xml load
 * @param node
 */
void BugGarbageFat::XmlLoad(wxXmlNode *node)
{
	Bug::XmlLoad(node);
	mFunc->XmlLoad(node);
}

/**
 * Draw fat bugs
 * @param graphics
 */
void BugGarbageFat::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	mFunc->Draw(graphics);
}

/**
 * On - click
 */
void BugGarbageFat::OnClick()
{
	return;
}

/**
 * On double click
 */
void BugGarbageFat::OnDClick()
{
	mFunc->OnDClick();
}

/**
 * Hit test x,y to see if they are clicking on this bug.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return true if clicked on bug
 */
bool BugGarbageFat::HitTest(double x, double y)
{
	return mFunc->HitTest(x, y);
}