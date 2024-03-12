/**
 * @file ItemVisitor.h
 * @author Will Feddern
 *
 * Item visitor base class.
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_ITEMVISITOR_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_ITEMVISITOR_H

// Forward references to all item types
class BugFeature;
class BugGarbage;
class BugNull;
class BugRace;
class BugRedundancy;
class BugZombie;
class Program;

/** Item visitor base class */
class ItemVisitor
{
protected:
	/**
     * Constructor
     * Ensures this is an abstract class
     */
	ItemVisitor() {}

public:
	virtual ~ItemVisitor() {}

	/**
     * Visit a Program object
     * @param program Program we are visiting
     */
	virtual void VisitProgram(Program* program) {}

	/**
     * Visit a Feature object
     * @param feature Feature we are visiting
     */
	virtual void VisitFeature(BugFeature* feature) {}

	/**
     * Visit a Garbage Bug object
     * @param bug Bug we are visiting
     */
	virtual void VisitGarbageBug(BugGarbage* bug) {}

	/**
     * Visit a Null Bug object
     * @param bug Bug we are visiting
     */
	virtual void VisitNullBug(BugNull* bug) {}

	/**
     * Visit a Race Condition Bug object
     * @param bug Bug we are visiting
     */
	virtual void VisitRaceBug(BugRace* bug) {}

	/**
     * Visit a Redundancy Bug object
     * @param bug Bug we are visiting
     */
	virtual void VisitRedundancyBug(BugRedundancy* bug) {}

	/**
     * Visit a Zombie Bug object
     * @param bug Bug we are visiting
     */
	virtual void VisitZombieBug(BugZombie* bug) {}
};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_ITEMVISITOR_H
