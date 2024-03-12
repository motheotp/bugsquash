/**
 * @file BugGarbageFat.h
 * @author Shuwei Chen
 *
 *
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGGARBAGEFAT_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGGARBAGEFAT_H

#include "BugGarbage.h"
class BugFatFunc;

/**
 * Fat bug for garbage
 */
class BugGarbageFat : public BugGarbage
{
private:
	/// The code linked to this fat bug
	std::shared_ptr<BugFatFunc> mFunc = nullptr;
public:
	explicit BugGarbageFat(Level* level, std::shared_ptr<Program> program);
	void XmlLoad(wxXmlNode *node) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void OnClick() override;
	void OnDClick() override;
	bool HitTest(double x, double y) override;
};


#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGGARBAGEFAT_H
