/**
 * @file BugSquashView.h
 * @author Tyler Baird, Will Feddern, Shuwei Chen
 *
 * View for the game
 */

#ifndef PROJECT1_BUGSQUASHVIEW_H
#define PROJECT1_BUGSQUASHVIEW_H

#include <wx/wx.h>
#include "Scoreboard.h"
#include "Game.h"
class LevelManager;
/**
 * View class for our game
 */
class BugSquashView : public wxWindow {
private:
	/// The timer that allows for animation
	wxTimer mTimer;

	/// Stopwatch used to measure elapsed time
	wxStopWatch mStopWatch;

    ///  Game
    std::shared_ptr<Game> mGame = nullptr;

	///Scoreboard
	std::shared_ptr<Scoreboard> mScore = nullptr;

	/// The last stopwatch time
	long mTime = 0;

    void OnPaint(wxPaintEvent& event);
	void OnTimerTick(wxTimerEvent& event);
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftDDown(wxMouseEvent &event);

	void OnLoadLevel0(wxCommandEvent &event);
	void OnLoadLevel1(wxCommandEvent &event);
	void OnLoadLevel2(wxCommandEvent &event);
	void OnLoadLevel3(wxCommandEvent &event);

public:
    void Initialize(wxFrame* parent);

};



#endif //PROJECT1_BUGSQUASHVIEW_H
