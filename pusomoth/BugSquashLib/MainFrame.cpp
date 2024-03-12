/**
 * @file MainFrame.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "MainFrame.h"
#include "BugSquashView.h"
#include "ids.h"

using namespace std;

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Game",
           wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto gameView = new BugSquashView();
    gameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(gameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

	auto menuBar = new wxMenuBar();

	auto fileMenu = new wxMenu();
	auto helpMenu = new wxMenu();
	auto levelMenu = new wxMenu();
	auto viewMenu = new wxMenu();

	menuBar->Append(fileMenu, L"&File" );
	menuBar->Append(levelMenu, L"&Level");
	menuBar->Append(viewMenu, L"&View");
	menuBar->Append(helpMenu, L"&Help");

	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
	levelMenu->Append(IDM_ON_LEVEL_0, L"&Level 0", L"Load Level 0");
	levelMenu->Append(IDM_ON_LEVEL_1, L"&Level 1", L"Load Level 1");
	levelMenu->Append(IDM_ON_LEVEL_2, L"&Level 2", L"Load Level 2");
	levelMenu->Append(IDM_ON_LEVEL_3, L"&Level 3", L"Load Level 3");

	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	SetMenuBar(menuBar);
	CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);


}

/**
 * Exit menu option handlers
 * @param event the command event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

/**
 * About menu option handlers
 * @param about the command event
 */
void MainFrame::OnAbout(wxCommandEvent& about)
{
	wxMessageBox(L"Welcome to BugSquash!",
				 L"About BugSquash",
				 wxOK,
				 this);
}