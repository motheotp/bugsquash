/**
 * @file ZombieReviver.h
 * @author Will Feddern
 *
 * Visitor class to revive zombie bugs
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_ZOMBIEREVIVER_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_ZOMBIEREVIVER_H

#include "ItemVisitor.h"

/// Visitor class to find and revive zombie bugs
class ZombieReviver : public ItemVisitor
{
private:

public:
	void VisitZombieBug(BugZombie* bug) override;

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_ZOMBIEREVIVER_H
