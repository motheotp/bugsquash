/**
 * @file MainFrame.h
 * @author Tyler Baird
 *
 * The top-level (main) frame of the application
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H
#include <wx/wx.h>

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
	void OnExit(wxCommandEvent&);
	void OnAbout(wxCommandEvent&);

public:
    void Initialize();

};


#endif //PROJECT1_MAINFRAME_H
