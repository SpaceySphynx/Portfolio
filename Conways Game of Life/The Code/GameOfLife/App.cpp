#include "App.h"
#include "MainWindow.h"
#include "DrawingPanel.h"
#include "wx/image.h"

// Macro to intialize the Application and call OnInIt
wxIMPLEMENT_APP(App);

// Constructor
App::App() 
{

}

// Destructor
App::~App() 
{

}

// Overridden OnInit method from the wxApp class.
bool App::OnInit() 
{
	wxImage::AddHandler(new wxPNGHandler);			// Handler for png file type icons
	MainWindow* p_MainWindow = new MainWindow();	// Create a new instance of the MainWindow class
	p_MainWindow->Show();							// Display the main window to the user
	return true;
}