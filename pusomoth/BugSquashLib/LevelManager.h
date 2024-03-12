/**
 * @file LevelManager.h
 * @author ShuWei Chen
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_LEVELMANAGER_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_LEVELMANAGER_H

#include "Scoreboard.h"
#include "Level.h"

class Level;

class Game;
/**
 * A class that manage the level
 */
class LevelManager
{
private:
	/// board that we call update
	///std::shared_ptr<Scoreboard> mBoard = nullptr;

	/// current level we at
	int mCurrentLevel = 0;

	///scoreboard
	std::shared_ptr<Scoreboard> mScoreboard = nullptr;


	/// level of game
	std::shared_ptr<Level> mLevel = nullptr;

	/// resource directory
	std::wstring mResourceDir = L"";

	/// game
	Game* mGame = nullptr;

public:
	LevelManager(std::wstring resourceDir);

	/// Default constructor (disabled)
	LevelManager() = delete;

	/// Copy constructor (disabled)
	LevelManager(const LevelManager &) = delete;

	/// Assignment operator
	void operator=(const LevelManager &) = delete;

	void NextLevel();

	void ToLevel(int levelNum);

	void Update(double elapsed);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, double Width, double Height);

	/**
	 * Set resource dir
	 * @param dir
	 */
	void SetResourceDir(std::wstring dir) { mResourceDir = dir; }

	/**
	 * Get resource dir
	 * @return resource dir
	 */
	auto GetResourceDir() { return mResourceDir; }

	/// @return current scoreboard
	auto GetScoreboard() { return mScoreboard; }

	/// @return current level
    auto GetLevel() { return mLevel; }

	/// @return the number of programs in the level
	int GetNumPrograms() { return mLevel->GetNumPrograms(); }
	/// @return the number of bugs in the level (includes features)
	int GetNumBugs() { return mLevel->GetNumBugs(); }
	/// @return the number of null bugs in the level
	int GetNumBugsNull() { return mLevel->GetNumBugsNull(); }
	/// @return the number of garbage bugs in the level
	int GetNumBugsGarbage() { return mLevel->GetNumBugsGarbage(); }
	/// @return the number of redundancy bugs in the level
	int GetNumBugsRedundancy() { return mLevel->GetNumBugsRedundancy(); }
	/// @return the number of feature "bugs" in the level
	int GetNumBugsFeature() { return mLevel->GetNumBugsFeature(); }

	/**
	 * Get game
	 * @return
	 */
	auto GetGame() { return mGame; }

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_LEVELMANAGER_H
