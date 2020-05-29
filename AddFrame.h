#pragma once
#include "wx/wx.h"
#include "wx/sizer.h"


class AddFrame : public wxFrame
{
public:
	AddFrame();
	~AddFrame();
private:
	wxTextCtrl *firstname = nullptr;
	wxTextCtrl *lastname = nullptr;
	wxButton *enter = nullptr;
	wxButton *back = nullptr;
	wxStaticText *adduser = nullptr; 
	
	void EnterText(wxCommandEvent& event);
	void Back(wxCommandEvent& event);


	DECLARE_EVENT_TABLE()

	enum
	{
		BUTTON_ENTER = wxID_HIGHEST+1,
		BUTTON_BACK,
		TEXTCTRL_FIRST,
		TEXTCTRL_LAST
	};
		
	
		
};

