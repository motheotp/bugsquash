/**
 * @file BugFeature.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "BugFeature.h"
#include "Level.h"
#include "LevelManager.h"
#include "Scoreboard.h"

using namespace std;

/// The feature sprite image
const std::wstring FeatureImageName = L"images/feature.png";

/// The splat image
const std::wstring FeatureSplatImageName = L"images/feature-splat.png";

/// Number of sprite images
const int FeatureNumSpriteImages = 6;

/**
 * Feature Bug Constructor
 * @param level The level this bug belongs to
 * @param program The Program to move towards
*/
BugFeature::BugFeature(Level* level, shared_ptr<Program> program) :
	Bug(level, program, FeatureNumSpriteImages, FeatureImageName, FeatureSplatImageName)
{

}
/**
 * Add score to Oops
 */
void BugFeature::AddScore()
{
	GetLevel()->GetManager()->GetScoreboard()->IncreaseOops();
}

/**
 * Called when the bug reaches the program
 */
void BugFeature::OnReachProgram()
{
}