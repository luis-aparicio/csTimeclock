#pragma once
#include "wx/wx.h"
#include "cApp.h"
#include "Login.h"
#include "wxImagePanel.h"
#include "wx/sizer.h"
#include <wx/textfile.h>

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

	virtual bool OnInit();
	
	
private :
	Login* Logframe = nullptr;
	wxImagePanel* cLogo;
	
};

