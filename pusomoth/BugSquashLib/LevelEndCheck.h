/**
 * @file LevelEndCheck.h
 * @author Will Feddern
 *
 * Visitor class to check if the level is complete
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_LEVELENDCHECK_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_LEVELENDCHECK_H

#include "ItemVisitor.h"

/// Visitor class to check if the level is complete
class LevelEndCheck : public ItemVisitor
{
private:
	/// Boolean to check if the level should end
	bool mEnd = true;

public:
	void VisitFeature(BugFeature* feature) override;
	void VisitGarbageBug(BugGarbage* bug) override;
	void VisitNullBug(BugNull* bug) override;
	void VisitRaceBug(BugRace* bug) override;
	void VisitRedundancyBug(BugRedundancy* bug) override;
	void VisitZombieBug(BugZombie* bug) override;

	/**
	 * Get if this level should end
	 * @return True if the level should end, else False
	 */
	bool ShouldEnd() { return mEnd; }

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_LEVELENDCHECK_H
