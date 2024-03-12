/**
 * @file BugRace.h
 * @author Will Feddern
 *
 * Race Condition Bug feature, have to arrive in a specific order
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGRACE_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGRACE_H

#include "Bug.h"


/**
 * Class for the Race Condition Bug
 */
class BugRace : public Bug
{
private:
	/// ID for this Race Condition Bug
	int mId = 0;
	/// Remaining duration of freeze
	double mFreeze = 0.0;
protected:
	void UpdateSprite(double elapsed) override;


public:
	explicit BugRace(Level* level, std::shared_ptr<Program> program);

	void XmlLoad(wxXmlNode *node) override;

	/**
 	 * Get the Id of the race bug
	 * @returns int id of the race bug
	 */
	int GetId() { return mId;}

	/**
	 * Accept a visitor
	 * @param visitor The visitor we accept
	 */
	void Accept(ItemVisitor* visitor) override { visitor->VisitRaceBug(this); }

	void OnClick() override;
	void Update(double elapsed) override;
	void OnReachProgram() override;


	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;


};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGRACE_H
