/**
 * @file BugNullFat.h
 * @author Shuwei Chen
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGNULLFAT_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGNULLFAT_H

#include "BugNull.h"

class BugFatFunc;

/**
 * Fat bug for null
 */
class BugNullFat : public BugNull
{
private:
	/// fat functionality
	std::shared_ptr<BugFatFunc> mFunc = nullptr;
public:
	explicit BugNullFat(Level* level, std::shared_ptr<Program> program);
	bool HitTest(double x, double y) override;
	void XmlLoad(wxXmlNode *node) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void OnClick() override;
	void OnDClick() override;
};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGNULLFAT_H
