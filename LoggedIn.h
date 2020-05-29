#pragma once
#include "wx/wx.h"
#include "workday.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class LoggedIn : public wxFrame
{
	string currentuser;
	wxButton *in;
	wxButton *out;
	wxStaticText *currenth;
	wxStaticText *username;
	wxStaticText *status;
	wxTimer *timeupdate;
	wxStopWatch *clockedtime;
	wxTimer *currentclocked;
	vector <workday*> days;
	wxDateTime temptoday;
	wxMenuBar *MenuBar;
	wxMenu *FileMenu;
	const char *filename;
	bool clocked = false;
	int latestdate;

public:
	LoggedIn(wxFrame *parent, string name);
	~LoggedIn();
	void update(wxTimerEvent& event);
	void clockin(wxCommandEvent& event);
	void clockout(wxCommandEvent& event);
	void expo(wxCommandEvent& event);
	void prefedit(string command);
	void OnClose(wxCloseEvent &event);


	DECLARE_EVENT_TABLE()

	enum
	{
		BUTTON_IN = wxID_HIGHEST+1,
		BUTTON_OUT,
		EVT_TIMERUPD,
		EXPORT,
		CLOSE_ID
	};
};

