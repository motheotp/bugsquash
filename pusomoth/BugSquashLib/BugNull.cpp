/**
 * @file BugNull.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "BugNull.h"

using namespace std;

/// The bug sprite image
const wstring NullBugSpriteImageName = L"images/scarlet-gray-bug.png";

/// The splat image
const wstring NullBugSplatImageName = L"images/scarlet-gray-splat.png";

/// Number of sprite images
const int NullBugNumSpriteImages = 6;

/**
 * Null Bug Constructor
 * @param level The level this bug belongs to
 * @param program The Program to move towards
*/
BugNull::BugNull(Level* level, shared_ptr<Program> program) :
	Bug(level, program, NullBugNumSpriteImages, NullBugSpriteImageName, NullBugSplatImageName)
{

}