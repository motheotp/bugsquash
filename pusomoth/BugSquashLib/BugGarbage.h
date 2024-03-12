/**
 * @file BugGarbage.h
 * @author Thomas Sheehy, Shuwei Chen, Will Feddern
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGGARBAGE_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGGARBAGE_H

#include "Bug.h"

/**
 * Class for the Garbage Bug
 */
class BugGarbage : public Bug
{
private:

public:
	explicit BugGarbage(Level* level, std::shared_ptr<Program> program);

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitGarbageBug(this); }

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGGARBAGE_H
