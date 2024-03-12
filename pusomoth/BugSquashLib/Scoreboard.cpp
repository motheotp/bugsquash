/**
 * @file Scoreboard.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "Scoreboard.h"
#include <wx/graphics.h>

using namespace std;

/*
* Scoreboard Constructor
*/
Scoreboard::Scoreboard()
{
}

/**
 * Draw the ScoreLabel
 * @param graphics The device context to draw on
 * @param x The window width (double)
 * @param y The window height (double)
 */
void Scoreboard::OnDrawLabel(std::shared_ptr<wxGraphicsContext> graphics, double x, double y)
{

	const wxFont font(wxSize(0, 40),
					  wxFONTFAMILY_SWISS,
					  wxFONTSTYLE_NORMAL,
					  wxFONTWEIGHT_NORMAL);
	graphics->SetFont(font, wxColour(0, 200, 200));
	graphics->DrawText(wxString::Format("Fixed"), 125, 100);
	graphics->DrawText(wxString::Format("Missed"), x/2 - 85, 100);
	graphics->DrawText(wxString::Format("Oops"), x - 175, 100);
}

/**
 * Draw the three scores (Missed, Fixed, Oops)
 * @param graphics The device context to draw on
 * @param x The window width (double)
 * @param y The window height (double)
 */
void Scoreboard::Display(std::shared_ptr<wxGraphicsContext> graphics, double x, double y){
	graphics->PushState();
	const wxFont font(wxSize(0, 85),
					  wxFONTFAMILY_SWISS,
					  wxFONTSTYLE_NORMAL,
					  wxFONTWEIGHT_NORMAL);
	graphics->SetFont(font, wxColour(0, 200, 200));
	graphics->DrawText(wxString::Format(wxT("%i"), mFixed), 150, 20);
	graphics->DrawText(wxString::Format(wxT("%i"), mMissed), x/2 - 50, 20);
	graphics->DrawText(wxString::Format(wxT("%i"), mOops),x - 150, 20);
}

