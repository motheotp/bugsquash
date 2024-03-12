/**
 * @file RaceOrderChecker.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "RaceOrderChecker.h"
#include "BugRace.h"

/**
 * Visit a Race Condition Bug object
 * @param bug Bug we are visiting
 */
void RaceOrderChecker::VisitRaceBug(BugRace* bug)
{
	if (!bug->IsMissed() && bug->GetId() < mReachId)
	{
		mIsNext = false;
	}
}
