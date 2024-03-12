/**
 * @file BugZombie.h
 * @author Will Feddern
 *
 * Zombie Bug feature, revives when another bug is killed
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGZOMBIE_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGZOMBIE_H

#include "Bug.h"

/**
 * Class for the Zombie Bug
 */
class BugZombie : public Bug
{
private:
	/// Number of bugs that need to die before the zombie bug revives. 0 = already revived
	int mBugsUntilRevive = 0;



public:
	explicit BugZombie(Level* level, std::shared_ptr<Program> program);

	void XmlLoad(wxXmlNode *node) override;

	void ReviveCheck();

	/**
	 * Accept a visitor
	 * @param visitor The visitor we accept
	 */
	void Accept(ItemVisitor* visitor) override { visitor->VisitZombieBug(this); }

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGZOMBIE_H
