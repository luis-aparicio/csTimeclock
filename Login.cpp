#include "Login.h"

using namespace std;


Login::Login() : wxFrame(nullptr, wxID_ANY, "Cardinal Signs", wxPoint(400,100), wxSize(800,600))
{
	updateusers();

	MenuBar = new wxMenuBar();
	FileMenu = new wxMenu();
	
	
	FileMenu->Append(MENU_ADD, _T("&Add User"));
	MenuBar->Append(FileMenu, _T("&File"));
	SetMenuBar(MenuBar);
	
	
	wxPoint logpos(350,425);
	choicepos = wxPoint(325, 375);
	wxSize logsize(50, 25);
	wxPoint rpos(350,475);
	
	log = new wxButton(this, BUTTON_LOG, _T("Login"), logpos, logsize , 0);
	refresh = new wxButton(this,BUTTON_REFRESH,_T("Refresh"),rpos,logsize,0);
	users = new wxChoice(this,CHOICE_LOG,choicepos,wxDefaultSize,finalsend,wxCB_SORT,wxDefaultValidator,"user choice");

	
}

BEGIN_EVENT_TABLE(Login, wxFrame)
EVT_MENU(MENU_ADD,Login::AddUser)
EVT_BUTTON(BUTTON_REFRESH,Login::ButtonUpdate)
EVT_BUTTON(BUTTON_LOG,Login::Logfunt)
END_EVENT_TABLE() // The button is pressed

Login::~Login()
{

}

void Login::OnExit(wxCommandEvent& event)
{
	Close(TRUE); // Tells the OS to quit running this process
}

void Login::AddUser(wxCommandEvent& event)
{
	wxInitAllImageHandlers();
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	AddFrame *add = new AddFrame();
	cLogo = new wxImagePanel(add,wxT("Cardsignslogotransuser.png"),wxBITMAP_TYPE_PNG, 265, 50);
	sizer->Add(cLogo, 1, wxEXPAND);
	add->SetSizer(sizer);
	add->SetBackgroundColour(wxColour(0, 0, 153));
	add->Show();
}

void Login::updateusers()
{
	string name;
	if (FILE *file = fopen("users.txt", "r"))
	{
		ifstream users("users.txt");
		if (users.is_open())
		{
			while (getline(users, name))
			{
				User now(name);
				allusers.push_back(now);
				
			}
			
			users.close();
		}
	}

	else
	{
		ofstream users("users.txt");
		if (users.is_open())
		{
			users.close();
		}

	}

	for (int i = 0; i < allusers.size(); i++)
	{
		finalsend.Add(allusers[i].name, 1);
	}
}

void Login::ButtonUpdate(wxCommandEvent& event)
{
	vector<User> compare;
	string name;
	if (FILE *file = fopen("users.txt", "r"))
	{
		ifstream users("users.txt");
		if (users.is_open())
		{
			while (getline(users, name))
			{
				User now(name);
				compare.push_back(now);

			}

			users.close();
		}
	}

	else
	{
		ofstream users("users.txt");
		if (users.is_open())
		{
			users.close();
		}

	}

	int num;

	num = compare.size() - allusers.size();

	while (num > 0)
	{
		users->Append(compare[compare.size() - num].name);
		num--;
	}

	allusers = compare;
}

void Login::Logfunt(wxCommandEvent& event)
{
	wxString current = users->GetString(users->GetSelection());
	string fin = string(current.mb_str(wxConvUTF8));
	LoggedIn *logwin = new LoggedIn(this, fin);
	logwin->SetBackgroundColour(wxColour(0, 0, 153));
	logwin->Show();
	event.Skip();
}
