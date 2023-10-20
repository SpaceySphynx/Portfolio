#define GenerationIntervalID 11000
#define GridSizeOptionsTextID 11001
#define LivingColorOptionsTextID 11002
#define DeadColorOptionsTextID 11003
#define GridRandomOptionsTextID 11004
#define GridSeedRandomOptionsTextID 11005
#define LivingColorPickerID 11006
#define DeadColorPickerID 11007
#define RandomizeGridID 11008
#define RandomizeSeedID 11009
#define ResetSettingsID 11010

#include "OptionsMenu.h"
#include "wx/numdlg.h"

// Define the event table, mapping events to their respective handler functions.
wxBEGIN_EVENT_TABLE(OptionsMenu, wxDialog)
EVT_BUTTON(wxID_OK, OptionsMenu::OnOkClicked)
EVT_BUTTON(wxID_CANCEL, OptionsMenu::OnCancelClicked)
EVT_BUTTON(RandomizeGridID, OptionsMenu::OnRandomizeClick)
EVT_BUTTON(RandomizeSeedID, OptionsMenu::OnRandomizeWithSeedClick)
wxEND_EVENT_TABLE()

// Constructor for the OptionsMenu class. Initializes the menu dialog, sets up controls, 
// layouts, and assigns values based on the current settings.
OptionsMenu::OptionsMenu(wxWindow* parent, Settings* settings, DrawingPanel* drawingpanel) :
	wxDialog(parent, wxID_ANY, "Settings", wxDefaultPosition, wxSize(400, 300)), m_Settings(settings), p_DrawingPanel(drawingpanel)
{
	p_OptionsMainSizer = new wxBoxSizer(wxVERTICAL);	// Main vertical sizer for the OptionsMenu layout.
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 10, 10);	// Grid layout sizer for the controls and their descriptions.

	p_ButtonSizer = CreateButtonSizer(wxOK | wxCANCEL);	// Create default OK and CANCEL buttons.
	m_GridSizeSpin = new wxSpinCtrl(this, wxID_ANY);	// Spin control for grid size.
	m_GridSizeSpin->SetRange(10, 200);
	m_IntervalSpin = new wxSpinCtrl(this, wxID_ANY);	// Spin control for generation interval.
	m_IntervalSpin->SetRange(50, 1000);
	m_LivingColorPicker = new wxColourPickerCtrl(this, LivingColorPickerID, m_Settings->GetLivingColor());	// Color picker for living cells.
	m_DeadColorPicker = new wxColourPickerCtrl(this, DeadColorPickerID, m_Settings->GetDeadColor());	// Color picker for dead cells.

	// Add descriptions and controls to the grid layout sizer.
	gridSizer->Add(new wxStaticText(this, GridSizeOptionsTextID, "Grid Size:"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(m_GridSizeSpin, 1, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, GenerationIntervalID, "Interval (m/s):"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(m_IntervalSpin, 1, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, LivingColorOptionsTextID, "Living Cell Color:"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(m_LivingColorPicker, 1, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, DeadColorOptionsTextID, "Dead Cell Color:"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(m_DeadColorPicker, 1, wxEXPAND);

	// Create and add the randomize buttons to the grid layout.
	wxButton* m_RandomizeButton = new wxButton(this, RandomizeGridID, "Randomize");
	gridSizer->Add(m_RandomizeButton, 1, wxEXPAND);
	wxButton* m_RandomizeSeedButton = new wxButton(this, RandomizeSeedID, "Randomize with Seed");
	gridSizer->Add(m_RandomizeSeedButton, 1, wxEXPAND);

	// Allow the second column (controls) of the grid layout to expand with available space.
	gridSizer->AddGrowableCol(1, 1);

	// Add the grid layout and button sizers to the main layout sizer.
	p_OptionsMainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);
	p_OptionsMainSizer->Add(p_ButtonSizer, 0, wxEXPAND | wxALL, 10);

	// Assign values from the settings to the controls.
	m_GridSizeSpin->SetValue(m_Settings->m_GridSize);
	m_IntervalSpin->SetValue(m_Settings->m_MillisecondsTilNextGeneration);

	// Apply the main layout sizer to the dialog and adjust the dialog size based on the content.
	SetSizer(p_OptionsMainSizer);
	p_OptionsMainSizer->Fit(this);
}

// Destructor
OptionsMenu::~OptionsMenu()
{

}

// Method Description: Handles the event when the OK button is clicked in the OptionsMenu.
// It captures the current state of the controls in the dialog and updates the application's settings with these values.
void OptionsMenu::OnOkClicked(wxCommandEvent& event)
{
	// Update the settings with the values selected in the dialog.
	m_Settings->m_GridSize = m_GridSizeSpin->GetValue();
	m_Settings->m_MillisecondsTilNextGeneration = m_IntervalSpin->GetValue();
	m_Settings->SetLivingColor(m_LivingColorPicker->GetColour());
	m_Settings->SetDeadColor(m_DeadColorPicker->GetColour());

	m_Settings->SaveSettings();	// Commit the updated settings.

	// Close the dialog, signaling that the OK button was pressed.
	EndModal(wxID_OK);
}

// Method Description: Handles the event when the CANCEL button is clicked in the OptionsMenu.
// This method simply closes the dialog without applying any changes.
void OptionsMenu::OnCancelClicked(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);	// Close the dialog without applying changes.
}

// Method Description: Handles the event when the "Randomize" button is clicked in the OptionsMenu.
// It triggers the RandomizeGrid method of the associated drawing panel.
void OptionsMenu::OnRandomizeClick(wxCommandEvent& event)
{
	p_DrawingPanel->RandomizeGrid();	// Randomize the grid in the drawing panel.
}

// Method Description: Handles the event when the "Randomize with Seed" button is clicked in the OptionsMenu.
// This method prompts the user to input a seed value for grid randomization and, if provided, uses it for the randomization process.
void OptionsMenu::OnRandomizeWithSeedClick(wxCommandEvent& event)
{
	long seed = wxGetNumberFromUser("Enter seed for randomization:", "Seed:", "Randomize Seed", 0, 0, LONG_MAX, this);	// Prompt the user for a randomization seed.

	if (seed != -1) // Ensure the user didn't cancel the input dialog.
		p_DrawingPanel->RandomizeGrid(seed);	// Use the provided seed for grid randomization.
}
