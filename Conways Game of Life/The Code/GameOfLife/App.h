#pragma once

#include "wx/wx.h"

// Declaration of the App class inheriting from wxWidgets library
class App : public wxApp
{
public:
	App();					// Constructor
	~App();					// Destructor
	virtual bool OnInit();	// Override of the OnInit method from the wxApp class 

private:

};

