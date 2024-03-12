/**
 * @file BugFeature.h
 * @author Thomas Sheehy, Will Feddern
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGFEATURE_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGFEATURE_H

#include "Bug.h"

/**
 * Class for the Feature Bug
 */
class BugFeature : public Bug
{
private:

public:
	explicit BugFeature(Level* level, std::shared_ptr<Program> program);
	void AddScore() override;

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
    */
	void Accept(ItemVisitor* visitor) override { visitor->VisitFeature(this); }

	void OnReachProgram() override;
};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGFEATURE_H
