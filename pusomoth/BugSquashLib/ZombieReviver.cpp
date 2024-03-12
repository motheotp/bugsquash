/**
 * @file ZombieReviver.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "ZombieReviver.h"
#include "BugZombie.h"

/**
 * Visit a Zombie Bug object and call ReviveCheck
 * @param bug Bug we are visiting
 */
void ZombieReviver::VisitZombieBug(BugZombie* bug)
{
	bug->ReviveCheck();
}
