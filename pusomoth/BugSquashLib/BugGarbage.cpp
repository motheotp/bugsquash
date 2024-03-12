/**
 * @file BugGarbage.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "BugGarbage.h"
#include "LevelManager.h"
#include "Scoreboard.h"

using namespace std;

/// The bug sprite image
const std::wstring GarbageBugSpriteImageName = L"images/blue-maize-bug.png";

/// The splat image
const std::wstring GarbageBugSplatImageName = L"images/blue-maize-splat.png";

/// Number of sprite images
const int GarbageBugNumSpriteImages = 5;

/**
 * Feature Bug Constructor
 * @param level The level this bug belongs to
 * @param program The Program to move towards
*/
BugGarbage::BugGarbage(Level* level, shared_ptr<Program> program) :
	Bug(level, program, GarbageBugNumSpriteImages, GarbageBugSpriteImageName, GarbageBugSplatImageName)
{

}

