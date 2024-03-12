/**
 * @file BugFatFunc.h
 * @author Shuwei Chen, Thomas Sheehy
 *
 *
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGFATFUNC_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGFATFUNC_H
class Bug;
class Level;

/**
 * Class for fat bug with code and pass reg
 */
class BugFatFunc{
private:
	/// code
	std::wstring mCode = L"";
	/// validation
	std::wstring mPass = L"";

	bool IsPass(std::wstring code);

	/// The bug object this code is linked with
	Bug *mBug = nullptr;
public:
	explicit BugFatFunc(Bug* bug);

	void XmlLoad(wxXmlNode *node);

	void OnDClick();

	void DlgCallBack(std::wstring code);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	bool HitTest(double x, double y);
};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGFATFUNC_H
