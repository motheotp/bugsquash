/**
 * @file BugNullFat.cpp
 * @author Motheo Treasure Puso
 */
#include "pch.h"
#include "BugNullFat.h"
#include "BugFatFunc.h"
#include <wx/graphics.h>

/**
 * Constructor
 * @param level
 * @param program
 */
BugNullFat::BugNullFat(Level *level, std::shared_ptr<Program> program) : BugNull(level, program)
{
	mFunc = std::make_shared<BugFatFunc>(this);
}

/**
 * Xml load
 * @param node
 */
void BugNullFat::XmlLoad(wxXmlNode *node)
{
	Bug::XmlLoad(node);
	mFunc->XmlLoad(node);
}

/**
 * Draw fat bugs
 * @param graphics
 */
void BugNullFat::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	mFunc->Draw(graphics);
}

/**
 * On - click
 */
void BugNullFat::OnClick()
{
	return;
}

/**
 * On double click
 */
void BugNullFat::OnDClick()
{
	mFunc->OnDClick();
}

/**
 * Hit test x,y to see if they are clicking on this bug.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @return true if clicked on bug
 */
bool BugNullFat::HitTest(double x, double y)
{
	return mFunc->HitTest(x, y);
}