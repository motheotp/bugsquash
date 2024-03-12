/**
 * @file BugZombie.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "BugZombie.h"

using namespace std;

/// The bug sprite image
const wstring ZombieBugSpriteImageName = L"images/green-red-bug.png";

/// The splat image
const wstring ZombieBugSplatImageName = L"images/green-red-splat.png";

/// Number of sprite images
const int ZombieBugNumSpriteImages = 5;

/**
 * Zombie Bug Constructor
 * @param level The level this bug belongs to
 * @param program The Program to move towards
*/
BugZombie::BugZombie(Level* level, shared_ptr<Program> program) :
	Bug(level, program, ZombieBugNumSpriteImages, ZombieBugSpriteImageName, ZombieBugSplatImageName)
{
}

/**
 * Code Loading
 * @param node The Xml node we are loading the code from
 */
void BugZombie::XmlLoad(wxXmlNode *node)
{
	Bug::XmlLoad(node);
	node->GetAttribute(L"reviveCount", L"0").ToInt(&mBugsUntilRevive);
}

/**
 * Check if the zombie bug needs to be revived with another bug dies
 */
void BugZombie::ReviveCheck()
{
	if (IsSplat() && mBugsUntilRevive > 0)
	{
		mBugsUntilRevive--;

		if (mBugsUntilRevive == 0)
		{
			// Revive
			SetSplat(false);
		}
	}
}