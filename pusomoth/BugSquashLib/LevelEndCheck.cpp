/**
 * @file LevelEndCheck.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "LevelEndCheck.h"

#include "BugFeature.h"
#include "BugGarbage.h"
#include "BugNull.h"
#include "BugRace.h"
#include "BugRedundancy.h"
#include "BugZombie.h"



/**
 * Visit a Feature object
 * @param feature Feature we are visiting
 */
void LevelEndCheck::VisitFeature(BugFeature* feature)
{
	if (!feature->IsMissed() && !feature->IsSplat())
	{
		mEnd = false;
	}
}
/**
 * Visit a Garbage Bug object
 * @param bug Bug we are visiting
 */
void LevelEndCheck::VisitGarbageBug(BugGarbage* bug)
{
	if (!bug->IsMissed() && !bug->IsSplat())
	{
		mEnd = false;
	}
}
/**
 * Visit a Null Bug object
 * @param bug Bug we are visiting
 */
void LevelEndCheck::VisitNullBug(BugNull* bug)
{
	if (!bug->IsMissed() && !bug->IsSplat())
	{
		mEnd = false;
	}
}
/**
 * Visit a Race Condition Bug object
 * @param bug Bug we are visiting
 */
void LevelEndCheck::VisitRaceBug(BugRace* bug)
{
	if (!bug->IsMissed() && !bug->IsSplat())
	{
		mEnd = false;
	}
}
/**
 * Visit a Redundancy Bug object
 * @param bug Bug we are visiting
 */
void LevelEndCheck::VisitRedundancyBug(BugRedundancy* bug)
{
	if (!bug->IsMissed() && !bug->IsSplat())
	{
		mEnd = false;
	}
}
/**
 * Visit a Zombie Bug object
 * @param bug Bug we are visiting
 */
void LevelEndCheck::VisitZombieBug(BugZombie* bug)
{
	if(!bug->IsMissed() && !bug->IsSplat())
	{
		mEnd = false;
	}
}