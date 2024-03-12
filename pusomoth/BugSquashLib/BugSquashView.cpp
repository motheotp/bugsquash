/**
 * @file BugSquashView.cpp
 * @author Motheo Treasure Puso
 */


#include "pch.h"
#include "BugSquashView.h"
#include "ids.h"
#include "LevelManager.h"

#include <wx/dcbuffer.h>
#include <wx/stdpaths.h>
#include <wx/graphics.h>
#include <wx/filename.h>

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void BugSquashView::Initialize(wxFrame *parent) {
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &BugSquashView::OnPaint, this);
	Bind(wxEVT_TIMER, &BugSquashView::OnTimerTick, this);
	Bind(wxEVT_LEFT_DOWN, &BugSquashView::OnLeftDown, this);
	Bind(wxEVT_LEFT_DCLICK, &BugSquashView::OnLeftDDown, this);

	// Determine where the images are stored
	//auto standardPaths = wxStandardPaths::Get();
	//wxStandardPaths& standardPaths = wxStandardPaths::Get();
	//std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();

	wstring resourcesDir = L"../resources";
	wxFileName filename(resourcesDir);

	mGame = make_shared<Game>();
	mGame->Initialize();

	auto levelMenu = new wxMenu();
	levelMenu->Append(IDM_ON_LEVEL_0, L"Level 0", L"Jump to level 1");
	levelMenu->Append(IDM_ON_LEVEL_1, L"Level 1", L"Jump to level 1");
	levelMenu->Append(IDM_ON_LEVEL_2, L"Level 2", L"Jump to level 1");
	levelMenu->Append(IDM_ON_LEVEL_3, L"Level 3", L"Jump to level 1");

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &BugSquashView::OnLoadLevel0, this, IDM_ON_LEVEL_0);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &BugSquashView::OnLoadLevel1, this, IDM_ON_LEVEL_1);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &BugSquashView::OnLoadLevel2, this, IDM_ON_LEVEL_2);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &BugSquashView::OnLoadLevel3, this, IDM_ON_LEVEL_3);

	mTimer.SetOwner(this);
	mTimer.Start(FrameDuration);
	mStopWatch.Start();
}
/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void BugSquashView::OnPaint(wxPaintEvent &event) {
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

	// Compute the time that has elapsed
	// since the last call to OnPaint.
	auto newTime = mStopWatch.Time();
	auto elapsed = (double)(newTime - mTime) * 0.001;
	mTime = newTime;

	mGame->Update(elapsed);

    // Create a graphics context
    auto gc = shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame->OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event
 */
void BugSquashView::OnLeftDown(wxMouseEvent &event)
{
	mGame->OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Timer event handler
 * @param event Timer event
 */
void BugSquashView::OnTimerTick(wxTimerEvent& event)
{
	Refresh();
}

/**
 * On choose level 0
 * @param event
 */
void BugSquashView::OnLoadLevel0(wxCommandEvent &event)
{
	mGame->ToLevel(0);
}
/**
 * On choose level 1
 * @param event
 */
void BugSquashView::OnLoadLevel1(wxCommandEvent &event)
{
	mGame->ToLevel(1);

}
/**
 * On choose level 2
 * @param event
 */
void BugSquashView::OnLoadLevel2(wxCommandEvent &event)
{
	mGame->ToLevel(2);

}
/**
 * On choose level 3
 * @param event
 */
void BugSquashView::OnLoadLevel3(wxCommandEvent &event)
{
	mGame->ToLevel(3);

}
/**
 * When mouse double clicked
 * @param event
 */
void BugSquashView::OnLeftDDown(wxMouseEvent &event)
{
	mGame->OnLeftDDown(event.GetX(), event.GetY());
}


