#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include "Settings.h"
#include "DrawingPanel.h"

class DrawingPanel; // Forward declaration used to prevent cyclic dependencies.

// The OptionsMenu class represents the dialog allowing users to modify game settings.
// It derives from the wxDialog class provided by wxWidgets.
class OptionsMenu : public wxDialog
{
public:
    OptionsMenu(wxWindow* parent, Settings* settings, DrawingPanel* drawingpanel);  // Constructor: Initializes the options menu with a given parent window, settings object, and drawing panel.
    ~OptionsMenu(); // Destructor

private:

    Settings* m_Settings = nullptr;                 // Pointer to the settings object, which allows access to and modification of game configurations.
    DrawingPanel* p_DrawingPanel = nullptr;         // Pointer to the drawing panel to refresh and apply the modified settings.
    wxBoxSizer* p_OptionsMainSizer = nullptr;       // Main vertical box sizer: Helps align all child controls and sizers vertically within the dialog.
    wxSizer* p_ButtonSizer = nullptr;               // Box sizer for the OK and CANCEL buttons at the bottom.
    wxSpinCtrl* m_GridSizeSpin;                     // Spin control to adjust grid size: Allows the user to specify a grid size through a spin control.
    wxSpinCtrl* m_IntervalSpin;                     // Spin control to adjust interval time between gnerations: Allows the user to specify a interval through a spin control.
    wxColourPickerCtrl* m_LivingColorPicker;        // Color pickers: Enables users to select colors for living cells.
    wxColourPickerCtrl* m_DeadColorPicker;          // Color pickers: Enables users to select colors for dead cells.

    void OnOkClicked(wxCommandEvent& event);        // Event handler for OK button: Saves any changes made in the dialog to the settings.
    void OnCancelClicked(wxCommandEvent& event);    // Event handler for CANCEL button: Discards any changes made and closes the dialog.
    void OnRandomizeClick(wxCommandEvent& event);   // Event handler for the randomize grid button.
    void OnRandomizeWithSeedClick(wxCommandEvent& event);   // Event handler for the randomize grid with seed button.
    wxDECLARE_EVENT_TABLE();                        // A macro to declare an event table: This sets up the wxWidgets event handling system.
};
