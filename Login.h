#pragma once
#include "AddFrame.h"
#include "User.h"
#include "LoggedIn.h"
#include <fstream>
#include <iostream>
#include "wx/wx.h"
#include "wx/sizer.h"
#include "wxImagePanel.h"

class Login : public wxFrame
{
public:
	Login();
	~Login();
	bool open;

private:
	
	wxButton * log;
	wxButton * refresh;
	wxMenuBar *MenuBar;
	wxMenu *FileMenu;
	wxImagePanel* cLogo;
	wxChoice *users;
	vector<User> allusers;
	wxArrayString finalsend;
	wxPoint choicepos;
	
	void OnExit(wxCommandEvent& event);
	void AddUser(wxCommandEvent& event);
	void ButtonUpdate(wxCommandEvent& event);
	void Logfunt(wxCommandEvent& event);
	void updateusers();
	
	DECLARE_EVENT_TABLE()

	enum
	{
		BUTTON_LOG = wxID_HIGHEST + 1,
		MENU_ADD,
		BUTTON_REFRESH,
		CHOICE_LOG,
		
	};


	
};

