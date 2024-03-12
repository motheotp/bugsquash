/**
 * @file CodeDlg.h
 * @author Shuwei Chen, Thomas Sheehy
 *
 *
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_CODEDLG_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_CODEDLG_H
class BugFatFunc;
/**
 * Code dialog
 */
class CodeDlg : public wxDialog
{
private:
	/// input for us to get value
	wxTextCtrl* mInput = nullptr;
	/// bug that trigger this dlg
	BugFatFunc* mBug = nullptr;

	void OnOk(wxCommandEvent & event);

	void OnClose(wxCloseEvent& event);

	void ValidateCode();
public:
	/// Default constructor (disabled)
	CodeDlg() = delete;

	/// Copy constructor (disabled)
	CodeDlg(const CodeDlg &) = delete;

	/// Assignment operator
	void operator=(const CodeDlg &) = delete;

	CodeDlg(std::wstring code, BugFatFunc* bug);
};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_CODEDLG_H
