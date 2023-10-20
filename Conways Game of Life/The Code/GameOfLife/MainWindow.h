#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include "Settings.h"
#include "FileMenu.h"

class MainWindow : public wxFrame           // MainWindow: Manages the primary user interface elements and core logic for the Game of Life.
{
public:
    MainWindow();                           // Constructor: Initializes the main window and its widgets.
    ~MainWindow();                          // Destructor: Cleans up resources used by the window.
    wxDECLARE_EVENT_TABLE();                // Macro table for handling wxWidgets events.

private:
    std::string m_CurrentFilePath = "";     // Current file path being used for saving or loading patterns.
    wxBoxSizer* p_Sizer = nullptr;          // Sizer: Adjusts layout when the window resizes.
    wxToolBar* p_ToolBar = nullptr;         // Toolbar: Contains buttons for play, pause, next generation, etc.
    DrawingPanel* p_DrawingPanel = nullptr; // Drawing Panel: Custom panel to display the Game of Life grid.
    wxStatusBar* p_StatusBar = nullptr;     // Status Bar: Shows game statistics (e.g., generation count) at the window's bottom.
    wxTimer* p_Timer = nullptr;             // Timer: Progresses the game state at regular intervals.
    wxMenuBar* p_MenuBar = nullptr;         // Menu Bar: Provides top-level navigation and settings.
    wxMenu* p_FileMenu = nullptr;           // File-related actions (e.g., Open, Save).
    wxMenu* p_ViewMenu = nullptr;           // Display options (e.g., Show Grid).
    wxMenu* p_OptionsMenu = nullptr;        // Game preferences.
    wxMenuItem* p_FiniteMenuItem = nullptr; // Menu Items for boundary type (Finite or Toroidal).
    wxMenuItem* p_ToroidalMenuItem = nullptr;

    std::vector<std::vector<bool>> ReadPatternFromFile(const std::string& filePath);                // Reads a Game of Life pattern from a file.
    std::tuple<int, int, int, int> GetBoundingBox(const std::vector<std::vector<bool>>& pattern);   // Computes bounding box for a given pattern.
    std::vector<std::vector<bool>> m_GameBoard;             // Game Board: 2D vector representing grid. Cells can be true (alive) or false (dead).
    std::vector<int> m_StatusBarTextWidths = { -1,-1 };     // Status Bar Text Widths: Defines sections e.g., Generations | Living Cells.
    std::vector<std::vector<int>> m_NeighborCounts;         // Neighbor Counts: 2D vector storing living neighbor count for each cell.

    Settings m_Settings;                                // Game Settings: Contains settings like cell color, grid visibility, etc.

    // Initialization Methods
    void InitializeGUIComponents();                     // Sets up GUI components.
    void LoadSettings();                                // Loads user-defined or default settings.
    void InitializeGameBoard();                         // Sets game board to its starting state.
    void SetupToolBar();                                // Sets up the toolbar with buttons.
    void SetupMenuBar();                                // Sets up the menu bar with different menus.

    // Game Logic Methods
    void SetStatusText();                               // Updates the status bar with current game stats.
    void NextGeneration();                              // Moves game state to the next generation.
    int CalculateNeighborCount(int x, int y);           // Counts living neighbors for a given cell.

    // Event Handlers
    void OnSizeChange(wxSizeEvent& event);              // Window resize event.
    void OnPlayButton(wxCommandEvent& event);           // Play button clicked.
    void OnPauseButton(wxCommandEvent& event);          // Pause button clicked.
    void OnNextButton(wxCommandEvent& event);           // Next generation button clicked.
    void OnClearButton(wxCommandEvent& event);          // Clear board button clicked.
    void OnTimerEvent(wxTimerEvent& event);             // Timer events for auto progression.
    void OnSettingsMenuClick(wxCommandEvent& event);    // Open settings dialog.
    void OnShowNeighborCount(wxCommandEvent& event);    // Toggle neighbor count display.
    void OnMouseClick(wxMouseEvent& event);             // Clicking on a cell on the board.
    void OnNewClick(wxCommandEvent& event);             // New game.
    void OnFileOpenClick(wxCommandEvent& event);        // Open pattern file.
    void OnFileSaveClick(wxCommandEvent& event);        // Save current pattern.
    void OnFileSaveAsClick(wxCommandEvent& event);      // Save current pattern with a new name.
    void OnExitClick(wxCommandEvent& event);            // Exit the application.
    void UpdateNeighborCounts();                        // Update the neighbor count for each cell.
    void SaveGameStateToFile(const std::string& path);  // Save current game state.
    void OnFileImportClick(wxCommandEvent& event);      // Import a pattern.
    void OnResetToDefaultClick(wxCommandEvent& event);  // Reset settings to default values.
    void OnFiniteMenuClick(wxCommandEvent& event);      // Set boundary to finite mode.
    void OnToroidalMenuClick(wxCommandEvent& event);    // Set boundary to toroidal mode.
    void OnToggleShowGrid(wxCommandEvent& event);       // Toggle the visibility of the main grid.
    void OnToggleShow10x10Grid(wxCommandEvent& event);  // Toggle visibility of the 10x10 grid.
    void OnToggleShowHUD(wxCommandEvent& event);        // Toggle heads-up display (HUD) settings.

};