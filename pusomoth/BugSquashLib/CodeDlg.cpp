/**
 * @file CodeDlg.cpp
 * @author Motheo Treasure Puso
 */
#include "pch.h"
#include "CodeDlg.h"
#include "BugFatFunc.h"

/// title
const std::wstring Title = L"Bug Squash IDE";

/**
 * Constructor
 * @param code the code string
 * @param bug the bug linked with the code
 */
CodeDlg::CodeDlg(std::wstring code, BugFatFunc* bug):
	wxDialog(nullptr, wxID_ANY, Title, wxDefaultPosition, wxSize(800, 600)), mBug(bug)
{
	Bind(wxEVT_CLOSE_WINDOW, &CodeDlg::OnClose, this);
	wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);

	mInput = new wxTextCtrl(this, wxID_ANY, L"", wxDefaultPosition, wxSize(760, 500), wxTE_MULTILINE);
	mInput->SetValue(code);
	box->Add(mInput, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	auto button = new wxButton(this, -1, L"OK");
	button->Bind(wxEVT_BUTTON, &CodeDlg::OnOk, this);
	box->Add(button, 2 , wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
	SetSizer(box);
	Center();
}

/**
 * On ok clicked
 * @param event
 */
void CodeDlg::OnOk(wxCommandEvent &event)
{
	ValidateCode();
}

/**
 * When close dlg
 * @param event
 */
void CodeDlg::OnClose(wxCloseEvent &event)
{
	ValidateCode();
}

/**
 * ValidateCode call
 */
void CodeDlg::ValidateCode()
{
	if(mBug)
		mBug->DlgCallBack(mInput->GetValue().ToStdWstring());
	Destroy();
}