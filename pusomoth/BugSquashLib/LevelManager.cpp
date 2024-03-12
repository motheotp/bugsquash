/**
 * @file LevelManager.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "LevelManager.h"
#include "Scoreboard.h"
#include "Level.h"
#include "Game.h"

using namespace std;

/// level filenames
const std::vector<std::wstring> LevelFileNames = {L"./data/level0.xml", L"./data/level1.xml", L"./data/level2.xml", L"./data/level3.xml"};

/// max level num we have
const int MaxLevelNum = 3;

/**
 * constructor
 * @param resources resources
 */
LevelManager::LevelManager(std::wstring resources)
{
	mScoreboard = make_shared<Scoreboard>();
	ToLevel(0);
}

/**
 * To giving level
 * @param levelNum
 */
void LevelManager::ToLevel(int levelNum)
{
	mScoreboard->SetScoreToZero();
	mLevel = std::make_shared<Level>(levelNum, this, LevelFileNames[levelNum % LevelFileNames.size()]);
	mCurrentLevel = levelNum % LevelFileNames.size();
}
/**
 * To next level
 */
void LevelManager::NextLevel()
{
	ToLevel((mCurrentLevel + 1) % MaxLevelNum);
}

/**
 * Update the level
 * @param elapsed
 */
void LevelManager::Update(double elapsed)
{
	if(mLevel != nullptr) {
		mLevel->Update(elapsed);
	}
}

/**
 * Draw the Level
 * @param graphics The device context to draw on
 * @param Width The width of graphics
 * @param Height The height of graphics
 */
void LevelManager::Draw(shared_ptr<wxGraphicsContext> graphics, double Width, double Height)
{
	if(mLevel != nullptr) {
		mLevel->Draw(graphics);
		mScoreboard->OnDrawLabel(graphics, Width, Height);

		mScoreboard->Display(graphics, Width, Height);
	}
}
