#include "LoggedIn.h"



LoggedIn::LoggedIn(wxFrame *parent, string name) : wxFrame(parent,wxID_ANY,name, wxPoint(400, 100), wxSize(800, 600))
{
	//temptoday = wxDateTime::UNow();
	status = new wxStaticText(this, wxID_ANY, "", wxPoint(300, 125), wxDefaultSize, 0, "status");
	status->SetFont(wxFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	string now;
	string filen = name + ".txt";
	string prefname = name + "prefs.txt";
	const char* prefna = prefname.c_str();
	filename = filen.c_str();

	if (FILE *file = fopen(filename, "r"))
	{
		ifstream days(filename);
		if (days.is_open())
		{
			while (getline(days, now))
			{

			}
			if(now[0] == ' ')
			{ 
			string num = now.substr(13,2);
			latestdate = stoi(num);
			}

			days.close();
		}
	}

	else
	{
		ofstream days(filename);
		if (days.is_open())
		{
			days.close();
		}

	}

	if (FILE *file = fopen(prefna, "r"))
	{
		ifstream lastprefs(prefna);
		if (lastprefs.is_open())
		{
			while (getline(lastprefs, now))
			{
				if (now == "true")
				{
					clocked = true;
					status->SetForegroundColour(wxColour(0, 255, 0));
					status->SetLabel("CLOCKED IN");
				}
				else
				{
					status->SetForegroundColour(wxColour(255, 0, 0));
					status->SetLabel("CLOCKED OUT");
				}
			}
			
			lastprefs.close();
		}
	}

	else
	{
		ofstream lastprefs(filename);
		if (lastprefs.is_open())
		{
			lastprefs.close();
		}

	}

	timeupdate = new wxTimer(this, EVT_TIMERUPD);
	currentuser = name;
	
	in = new wxButton(this, BUTTON_IN, "CLOCK IN", wxPoint(200, 300), wxSize(200, 200), 0, wxDefaultValidator, "Clock In");
	out = new wxButton(this, BUTTON_OUT, "CLOCK OUT", wxPoint(400, 300), wxSize(200, 200), 0, wxDefaultValidator, "Clock Out");
	currenth = new wxStaticText(this, wxID_ANY, wxNow(), wxPoint(150, 200), wxDefaultSize, 0, "time");
	username = new wxStaticText(this, wxID_ANY, name, wxPoint(300, 100), wxDefaultSize, 0, "user");
	
	MenuBar = new wxMenuBar();
	FileMenu = new wxMenu();
	FileMenu->Append(EXPORT, _T("&Export"));
	MenuBar->Append(FileMenu, _T("&File"));
	SetMenuBar(MenuBar);

	currenth->SetFont(wxFont(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
	username->SetFont(wxFont(18, wxFONTFAMILY_MODERN, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

	clockedtime = new wxStopWatch();
	
	username->SetForegroundColour(wxColour(244, 244, 244));
	currenth->SetForegroundColour(wxColour(244, 244, 244));
	timeupdate->Start(1000);
}

LoggedIn::~LoggedIn()
{
}

BEGIN_EVENT_TABLE(LoggedIn, wxFrame)
EVT_TIMER (EVT_TIMERUPD,LoggedIn::update)
EVT_BUTTON (BUTTON_IN,LoggedIn::clockin)
EVT_BUTTON (BUTTON_OUT,LoggedIn::clockout)
EVT_MENU (EXPORT,LoggedIn::expo)
EVT_CLOSE (LoggedIn::OnClose)
END_EVENT_TABLE()

void LoggedIn::update(wxTimerEvent& event)
{
	currenth->SetLabel(wxNow());
	event.Skip();
}

void LoggedIn::clockin(wxCommandEvent & event)
{
	wxDateTime today = wxDateTime::UNow();
	//wxString tempday = today.GetWeekDayName(today.GetWeekDay(), wxDateTime::Name_Abbr);
	//string weekday = string(tempday.mb_str(wxConvUTF8));
	//string line;
	
	if (clocked)
	{
		return;
	}
	/*
	
		//write to the same line due to the same day 
		ofstream days(currentuser + ".txt", ios_base::out | ios_base::app);
		if (days.is_open())
		{
			
			days << " In: " + wxNow() +" ";
			//days << wxNow().SubString(8, 10);
		
			status->SetLabel("CLOCKED IN");
			days.close();
		}
		
		clocked = true;
		return;
	}
	*/

	ofstream days(currentuser+".txt", ios_base::app | ios_base::out);
		if (days.is_open())
		{
			if (latestdate != today.GetDay() && latestdate != 0)
			{
				days << "\n";
				days << "------------------------------------";
			}
			days << "\n";
			days << " In: "+ wxNow()+" ";
			//days << wxNow().SubString(8, 10);
			status->SetForegroundColour(wxColour(0, 255, 0));
			status->SetLabel("CLOCKED IN");
			clockedtime->Start();
			days.close();
		}
		prefedit("true");
		clocked = true;
		
}

void LoggedIn::clockout(wxCommandEvent & event)
{
	wxDateTime today = wxDateTime::UNow();
	//wxString tempday = today.GetWeekDayName(today.GetWeekDay(), wxDateTime::Name_Abbr);
	//string weekday = string(tempday.mb_str(wxConvUTF8));
	//string line;
	
	if (!clocked)
	{
		return;
	}
	
	ofstream days(currentuser + ".txt", ios_base::out | ios_base::app);
	if (days.is_open())
		{	
			clockedtime->Pause();
			float hours = (float)clockedtime->Time() / 3600000;
			days << " Out: " + wxNow() +" ,/";
			days << hours;
			days << " ";
			
			//days << wxNow().SubString(8, 10);
			status->SetForegroundColour(wxColour(255, 0, 0));
			status->SetLabel("CLOCKED OUT");
			days.close();
		}
		prefedit("false");
		clocked = false;
		return;
	
}

void LoggedIn::expo(wxCommandEvent & event)
{
	string send;
	string stream;
	string cday;
	string chours;
	workday * sday = new workday (0,"");
	float shours;
	bool sameday = false;

	string ifs = currentuser + ".txt";
	if (!clocked)
	{
		ifstream expo(ifs);
		if (expo.is_open())
		{
			while (getline(expo, send)) 
			{	
				stringstream now(send);
				while (getline(now,stream,','))

					if (stream[0] == ' ')
					{
						if (stream.substr(5, 10) == cday)
						{
							sameday = true;
							continue;
						}
						cday = stream.substr(5, 10);
						sameday = false;
					}
					else
					{
						if (sameday)
						{
							sday->totalhours += stof(stream.substr(1, stream.size() - 2));

							continue;
						}
						sday = new workday(0, "");
						shours = stof(stream.substr(1, stream.size() - 2));
						sday->totalhours = shours;
						sday->date = cday;
						days.push_back(sday);
					}
				
			}
			expo.close();
		}
		expo.open(ifs, ios::out | ios::trunc);
		expo.close();
		ofstream expof("Period of "+ days[0]->date + " " + currentuser +".txt");
		if (expof.is_open())
		{
			float totalhours = 0;
			for (int i = 0; i < days.size(); i++)
			{
				expof << days[i]->date + " Hours: " << setprecision(2) << days[i]->totalhours << "\n";
				totalhours += days[i]->totalhours;
			}
			expof << "Total hours for pay period: " << setprecision(2) << totalhours;
			expof.close();
			status->SetLabel("Export Complete!");
		}

		for (int i = 0; i < days.size(); i++)
		{
			delete (days[i]);
		}
		days.clear();
	}
}

void LoggedIn::prefedit(string command)
{

	ofstream pref(currentuser +"prefs.txt");
	if (pref.is_open())
	{	
		pref << command; 
		pref.close();
	}
}

void LoggedIn::OnClose(wxCloseEvent & event)
{
	event.Skip();
	this->Close(true);
}
