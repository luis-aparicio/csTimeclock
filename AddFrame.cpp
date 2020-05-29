#include "AddFrame.h"
#include "cApp.h"
#include <iostream>
#include <fstream>
#include <ios>

using namespace std;



AddFrame::AddFrame() : wxFrame(nullptr, wxID_ANY, "Cardinal Signs - Add User", wxPoint(400, 100), wxSize(800, 600))
{
	wxFont textfont(22, wxFONTFAMILY_MODERN, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD);
	wxPoint firstpoint(200,300);
	wxSize firstsize(150, 25);
	wxPoint lastpoint(400, 300);
	wxPoint enterpoint(250, 400);
	wxPoint backpoint(450, 400);
	wxPoint textpoint(210, 225);
	wxSize textsize(300, 300);
	wxSize entersize(50, 25);

	adduser = new wxStaticText(this, wxID_ANY, "Enter New User Name:", textpoint, wxDefaultSize , wxALIGN_CENTRE_HORIZONTAL, "add user");
	firstname = new wxTextCtrl(this, TEXTCTRL_FIRST, "Enter First Name", firstpoint, firstsize, wxTE_RICH2|wxTE_PROCESS_TAB, wxDefaultValidator, wxTextCtrlNameStr);
	lastname = new wxTextCtrl(this, TEXTCTRL_LAST, "Enter Last Name", lastpoint, firstsize, wxTE_RICH2|wxTE_PROCESS_TAB, wxDefaultValidator, wxTextCtrlNameStr);
	enter = new wxButton(this, BUTTON_ENTER, _T("&Enter"), enterpoint, entersize, 0);
	back = new wxButton(this, BUTTON_BACK, _T("&Back"), backpoint, entersize, 0);

	adduser->SetForegroundColour(wxColour(255,255,255));
	adduser->SetFont(textfont);
	
}

BEGIN_EVENT_TABLE(AddFrame, wxFrame)
EVT_BUTTON(BUTTON_BACK,AddFrame::Back)
EVT_BUTTON(BUTTON_ENTER,AddFrame::EnterText)
END_EVENT_TABLE() // The button is pressed


AddFrame::~AddFrame()
{
}

void AddFrame::EnterText(wxCommandEvent& event)
{
	string firstn;
	string lastn;

	firstn = firstname->GetLineText(0);
	lastn = lastname->GetLineText(0);
	
	ofstream users("users.txt", ios_base::app | ios_base::out);
	if (users.is_open())
	{
		
		users << firstn + " " + lastn +"\n";
		this->adduser->SetLabel("User Added!");
		users.close();
	}

}

void AddFrame::Back(wxCommandEvent& WXUNSED)
{
	this->Close();
}