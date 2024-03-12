/**
 * @file BugNull.h
 * @author Will Feddern
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGNULL_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGNULL_H

#include "Bug.h"

/**
 * Class for the Null Bug
 */
class BugNull : public Bug
{
private:

public:
	explicit BugNull(Level* level, std::shared_ptr<Program> program);

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitNullBug(this); }

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGNULL_H
