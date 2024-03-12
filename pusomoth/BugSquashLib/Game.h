/**
 * @file Game.h
 * @author Tyler Baird, Will Feddern
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include <wx/dc.h>
#include "Scoreboard.h"
#include "LevelManager.h"
class Item;
/**
 * The class for our Game
 */
class Game {
private:
	///An object that keeps track of score
	std::shared_ptr<Scoreboard> mScoreboard = nullptr;
	/// level manager
	std::shared_ptr<LevelManager> mLevelManager = nullptr;

	/// Whether or not game has shrunk
    bool mShrinked = false;

    /// Scale we are drawing at
    double mScale = 1;

    /// X offset when we draw
    double mXOffset = 0;

    /// Y offset when we draw
    double mYOffset = 0;

public:

    Game();

	// TODO: Game Init
	void Initialize();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
	void OnLeftDown(int x, int y);
	void OnLeftDDown(int x, int y);

	void Update(double elapsed);

	void ToLevel(int levelNum);
	double GetWidth();
	double GetHeight();

};


#endif //PROJECT1_GAME_H
