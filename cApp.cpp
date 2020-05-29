#include "stdafx.h"
#include "cApp.h"

#include <iostream>
#include <fstream>
using namespace std;

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}


cApp::~cApp()
{
}

bool cApp::OnInit()
{
  	
	wxInitAllImageHandlers();
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	
	Logframe = new Login();
	Logframe->SetBackgroundColour(wxColour(0, 0, 153));
	
	cLogo = new wxImagePanel(Logframe, wxT("Cardsignslogotrans.png"), wxBITMAP_TYPE_PNG,160,50);
	
	sizer->Add(cLogo, 1, wxEXPAND);
	
	Logframe->SetSizer(sizer);
	Logframe->Show();
	
	return true;
}

