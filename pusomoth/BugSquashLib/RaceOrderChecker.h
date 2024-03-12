/**
 * @file RaceOrderChecker.h
 * @author Will Feddern
 *
 * Visitor class to check race bug order
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_RACEORDERCHECKER_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_RACEORDERCHECKER_H

#include "ItemVisitor.h"

/// Visitor class to check race bug order
class RaceOrderChecker  : public ItemVisitor
{
private:
	/// Id of the Race Bug that reached the
	int mReachId = 0;
	/// If the Race Bug is the next that should arrive
	bool mIsNext = true;

public:
	void VisitRaceBug(BugRace* bug) override;

	/**
 	 * Set the Id of the race bug being tested
 	 * @param id Id of the race bug
	 */
	void SetReachId(int id) { mReachId = id; }

	/**
 	 * Get if the Race Bug is the next that should arrive
	 * @returns boolean true if the Race Bug is the next that should arrive
	 */
	bool GetIsNext() { return mIsNext; }


};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_RACEORDERCHECKER_H
