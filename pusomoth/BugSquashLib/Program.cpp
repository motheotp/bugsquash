/**
 * @file Program.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "Program.h"
#include <wx/graphics.h>

using namespace std;

/// Program filename
const wstring ProgramImageName = L"images/laptop.png";

/// name display padding
const double NamePadding = 0.4;

/// Program name font size
const int ProgramNameFontSize = 22;

/**
 * Program Constructor
 * @param level current level object
 * @param programName the name of the program
 */
Program::Program(Level* level, std::wstring& programName) : Item(level, ProgramImageName)
{
	mName = programName;
}

/**
 * Load the attributes for a program node.
 *
 * @param node The Xml node we are loading the program from
 */
void Program::XmlLoad(wxXmlNode* node)
{
	Item::XmlLoad(node);
	mName = node->GetAttribute(L"name", L"Program").ToStdWstring();
}

/**
 * Draw this program
 * @param graphics graphics to draw on
 */
void Program::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	Item::Draw(graphics);

	graphics->PushState();
	wxFont font(wxSize(0, ProgramNameFontSize),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);
	graphics->SetFont(font, *wxWHITE);
	double width, height;
	graphics->GetTextExtent(mName, &width, &height);

	if(width == 0) width = 1;
	if(height == 0) height = 1;

	double xFactor = GetWidth() / width - NamePadding;
	double yFactor = GetHeight() / height - NamePadding;
	double factor = xFactor > yFactor ? yFactor : xFactor;
	graphics->Translate(GetX(), GetY());

	if(factor < 1) {
		graphics->Scale(factor, factor);
	}

	graphics->DrawText(mName, -width / 2, -height / 2);
	graphics->PopState();
}