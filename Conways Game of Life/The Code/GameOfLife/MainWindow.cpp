// Defined constant values for buttons, timer and UIs.
#define ButtonPlayID 10001
#define ButtonPauseID 10002
#define ButtonNextID 10003
#define ButtonClearID 10004
#define GenerationTimerID 10005
#define MenuOptionsSettingsID 10006
#define ToggleNeighborDisplayID 10007
#define CellClickedID 10008
#define FileMenuNewID 10009
#define FileMenuImportID 10010
#define ResetToDefaultID 10011
#define MenuViewFiniteID 10012
#define MenuViewToroidalID 10013
#define MenuViewShowGridID 10014
#define MenuViewShow10x10GridID 10015
#define MenuViewShowHUDID 10016

#include "MainWindow.h"
#include "DrawingPanel.h"
#include "OptionsMenu.h"
#include "wx/filedlg.h"

// Event table: Maps specific events to their corresponding handler functions in the MainWindow class.
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_TOOL(ButtonPlayID, MainWindow::OnPlayButton)
	EVT_MENU(ButtonPlayID, MainWindow::OnPlayButton)
	EVT_MENU(ButtonPauseID, MainWindow::OnPauseButton)
	EVT_MENU(ButtonNextID, MainWindow::OnNextButton)
	EVT_MENU(ButtonClearID, MainWindow::OnClearButton)
	EVT_MENU(MenuOptionsSettingsID, MainWindow::OnSettingsMenuClick)
	EVT_MENU(ToggleNeighborDisplayID, MainWindow::OnShowNeighborCount)
	EVT_TIMER(GenerationTimerID, MainWindow::OnTimerEvent)
	EVT_MENU(wxID_OPEN, MainWindow::OnFileOpenClick)
	EVT_MENU(wxID_SAVE, MainWindow::OnFileSaveClick)
	EVT_MENU(wxID_SAVEAS, MainWindow::OnFileSaveAsClick)
	EVT_MENU(wxID_EXIT, MainWindow::OnExitClick)
	EVT_MENU(FileMenuNewID, MainWindow::OnNewClick)
	EVT_MENU(FileMenuImportID, MainWindow::OnFileImportClick)
	EVT_MENU(ResetToDefaultID, MainWindow::OnResetToDefaultClick)
	EVT_MENU(MenuViewFiniteID, MainWindow::OnFiniteMenuClick)
	EVT_MENU(MenuViewToroidalID, MainWindow::OnToroidalMenuClick)
	EVT_MENU(MenuViewShowGridID, MainWindow::OnToggleShowGrid)
	EVT_MENU(MenuViewShow10x10GridID, MainWindow::OnToggleShow10x10Grid)
	EVT_MENU(MenuViewShowHUDID, MainWindow::OnToggleShowHUD)
wxEND_EVENT_TABLE()

// Constructor: Initializes the main window, its widgets, and the game's initial state.
MainWindow::MainWindow() :
	wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100, 100), wxSize(600, 600))
{
	LoadSettings();				// Load the game settings from a temporary settings file.
	InitializeGUIComponents();	// Setup the primary GUI components for the main window.
	InitializeGameBoard();		// Set up the game board using the loaded settings.
	this->Layout();				// Arrange the GUI components.
}

// Destructor for the MainWindow class.
MainWindow::~MainWindow()
{
	m_Settings.SaveSettings();	// Persistently save settings before exiting.
	delete p_DrawingPanel;		// Clean up dynamically allocated resources.
	delete p_Timer;				// Clean up dynamically allocated resources.
}

// Initialize primary GUI components of the main window.
void MainWindow::InitializeGUIComponents()
{
	p_StatusBar = CreateStatusBar();											// Status bar at the bottom.
	p_ToolBar = CreateToolBar();												// Tool bar at the top.
	p_DrawingPanel = new 
		DrawingPanel(this, wxSize(100, 100), m_GameBoard, m_NeighborCounts);	// Main drawing area.
	p_Sizer = new wxBoxSizer(wxVERTICAL);										// Drawing space for Menu components.
	p_Timer = new wxTimer(this, GenerationTimerID);								// Timer for game updates.
	p_MenuBar = new wxMenuBar();												// Menu bar at the top.
	p_FileMenu = new wxMenu();													// File menu drop-down.
	p_ViewMenu = new wxMenu();													// View menu drop-down.
	p_OptionsMenu = new wxMenu();												// Options menu drop-down.
	p_FiniteMenuItem = 
		new wxMenuItem(p_ViewMenu, MenuViewFiniteID, "Finite", "", wxITEM_RADIO);
	p_ToroidalMenuItem = 
		new wxMenuItem(p_ViewMenu, MenuViewToroidalID, "Toroidal", "", wxITEM_RADIO);
	SetupToolBar();															// Call Method to setup the toolbar (play, pause, etc.).
	SetupMenuBar();															// Call Method to setup the top Menus (File, View, etc.).
}

// Loads the game settings. If a settings file exists, it's loaded.
void MainWindow::LoadSettings()

{
	std::ifstream m_SettingsFile("settings.bin");	// Check if there's an existing settings file.
	if (m_SettingsFile)								// If file exists then load the settings from the file.
	{
		m_Settings.LoadSettings();
	}
}

// Sets up the toolbar with its icons and corresponding functionalities.
void MainWindow::SetupToolBar()
{
	// Load and resize toolbar icons.
	wxBitmap playIcon(wxImage("play.png").Scale(m_Settings.m_IconWidth, m_Settings.m_IconHeight, wxIMAGE_QUALITY_HIGH));
	wxBitmap pauseIcon(wxImage("pause.png").Scale(m_Settings.m_IconWidth, m_Settings.m_IconHeight, wxIMAGE_QUALITY_HIGH));
	wxBitmap nextIcon(wxImage("next.png").Scale(m_Settings.m_IconWidth, m_Settings.m_IconHeight, wxIMAGE_QUALITY_HIGH));
	wxBitmap clearIcon(wxImage("stop.png").Scale(m_Settings.m_IconWidth, m_Settings.m_IconHeight, wxIMAGE_QUALITY_HIGH));
	// Setting up toolbar with icons and functionalities.
	p_ToolBar->AddTool(ButtonPlayID, "Play", playIcon);
	p_ToolBar->AddTool(ButtonPauseID, "Pause", pauseIcon);
	p_ToolBar->AddTool(ButtonNextID, "Next", nextIcon);
	p_ToolBar->AddTool(ButtonClearID, "Clear", clearIcon);
	// Provide short help text for each tool.
	p_ToolBar->SetToolShortHelp(ButtonPlayID, "Play the game");
	p_ToolBar->SetToolShortHelp(ButtonPauseID, "Pause the game");
	p_ToolBar->SetToolShortHelp(ButtonNextID, "Move to the next generation");
	p_ToolBar->SetToolShortHelp(ButtonClearID, "Clear the board");
	p_ToolBar->Realize();	// Finalize the toolbar's appearance.
}

// Configures the main window layout, menu bar, and binds relevant events.
void MainWindow::SetupMenuBar()
{
	p_Sizer->Add(p_DrawingPanel, 1, wxEXPAND | wxALL); // Add drawing panel to sizer with expansion properties.
	p_DrawingPanel->SetSettings(&m_Settings);  // Provide drawing panel with access to settings.

	// Bind mouse click event to drawing panel.
	p_DrawingPanel->Bind(wxEVT_LEFT_UP, &MainWindow::OnMouseClick, this);

	// Lambda to call the SetStatusText function from within DrawingPanel.
	p_DrawingPanel->CallSetStatusText([this]() { this->SetStatusText(); });

	// Add main menu categories to menu bar.
	p_MenuBar->Append(p_FileMenu, "File");
	p_MenuBar->Append(p_ViewMenu, "View");
	p_MenuBar->Append(p_OptionsMenu, "Options");

	// Configure the status bar for game status and statistics.
	p_StatusBar->SetFieldsCount(2);
	p_StatusBar->SetStatusWidths(m_StatusBarTextWidths.size(), &m_StatusBarTextWidths[0]);

	// Populate the options menu.
	p_OptionsMenu->Append(MenuOptionsSettingsID, "Settings", "Open the settings dialog");
	p_OptionsMenu->Append(ResetToDefaultID, "Reset to Default", "Reset all settings to their default values");

	// Set up the view menu with its various options and checkboxes.
	p_ViewMenu->AppendCheckItem(ToggleNeighborDisplayID, "Show Neighbor Count");
	p_ViewMenu->Check(ToggleNeighborDisplayID, m_Settings.GetShowNeighborCount());

	p_FiniteMenuItem->SetCheckable(true);
	p_ToroidalMenuItem->SetCheckable(true);
	p_ViewMenu->Append(p_FiniteMenuItem);
	p_ViewMenu->Append(p_ToroidalMenuItem);
	p_ViewMenu->Check(MenuViewFiniteID, !m_Settings.isToroidalMode);
	p_ViewMenu->Check(MenuViewToroidalID, m_Settings.isToroidalMode);

	p_ViewMenu->AppendCheckItem(MenuViewShowGridID, "Show Grid");
	p_ViewMenu->AppendCheckItem(MenuViewShow10x10GridID, "Show 10x10 Grid");
	p_ViewMenu->Check(MenuViewShowGridID, m_Settings.GetShowGrid());
	p_ViewMenu->Check(MenuViewShow10x10GridID, m_Settings.GetShow10x10Grid());

	p_ViewMenu->AppendCheckItem(MenuViewShowHUDID, "Show HUD");
	p_ViewMenu->Check(MenuViewShowHUDID, m_Settings.GetShowHUD());

	// Set up file menu items.
	p_FileMenu->Append(FileMenuNewID, "New", "Clear Game and Return to Default Settings");
	p_FileMenu->Append(wxID_OPEN);
	p_FileMenu->Append(wxID_SAVE);
	p_FileMenu->Append(wxID_SAVEAS);
	p_FileMenu->Append(FileMenuImportID, "Import", "Import .cells File");
	p_FileMenu->Append(wxID_EXIT);

	// Apply the created menu bar and sizer to the main window.
	SetMenuBar(p_MenuBar);
	SetSizer(p_Sizer);
}

// Event handler to dynamically adjust the DrawingPanel size when the MainWindow is resized.
void MainWindow::OnSizeChange(wxSizeEvent& event)
{
	p_DrawingPanel->SetSize(event.GetSize());	// Adjust the DrawingPanel's size to fit the new size of the MainWindow.
	p_DrawingPanel->Refresh();					// Redraw the DrawingPanel to reflect the changes.
	event.Skip();
}

// Sets up the game grid based on current settings and recalculates game statistics.
void MainWindow::InitializeGameBoard()
{
	m_NeighborCounts.resize(m_Settings.m_GridSize, std::vector<int>(m_Settings.m_GridSize, 0));  // Resize neighbor counts matrix to grid size and initialize to zeros.

	m_GameBoard.resize(m_Settings.m_GridSize);  // Adjust the game board's size based on settings.

	int liveCount = 0;  // Counter for live cells.
	// Iterate through the game board to count the living cells.
	for (const auto& row : m_GameBoard)
	{
		for (const auto& cell : row)
		{
			if (cell)  // If the cell is alive.
				liveCount++;
		}
	}
	m_Settings.m_LivingCells = liveCount;  // Update the living cells count.

	// Reset generation count if the game isn't in progress.
	if (!p_Timer->IsRunning())
	{
		m_Settings.m_Generations = 0;
	}

	p_DrawingPanel->SetGridSize(m_Settings.m_GridSize);  // Update the DrawingPanel with the new grid size for rendering.

	SetStatusText();  // Reflect the board initialization in the status text.
}

// Method to display the current game stats (generations & living cells) in the bottom status bar.
void MainWindow::SetStatusText()
{
	wxString generationsText = wxString::Format("Generations: %d", m_Settings.m_Generations);
	wxString livingCellsText = wxString::Format("Living Cells: %d", m_Settings.m_LivingCells);

	// Update the text in both fields of the status bar.
	p_StatusBar->SetStatusText(generationsText, 0);
	p_StatusBar->SetStatusText(livingCellsText, 1);
}

// Event handler to start the game's progression when the play button is clicked.
void MainWindow::OnPlayButton(wxCommandEvent& event)
{
	p_Timer->Start(m_Settings.m_MillisecondsTilNextGeneration);	// Start the timer for cell progression.
}

// Event handler to pause the game's progression when the pause button is clicked.
void MainWindow::OnPauseButton(wxCommandEvent& event)
{
	p_Timer->Stop();	// Stop the timer, pausing cell progression.
}

// Progresses the game state by one generation upon the next button click.
void MainWindow::OnNextButton(wxCommandEvent& event)
{
	NextGeneration();
}

// Resets the entire game grid and statistics upon the clear button click.
void MainWindow::OnClearButton(wxCommandEvent& event)
{
	p_Timer->Stop();  // Halt the game progression.

	// Iterate over each cell in the grid.
	for (int x = 0; x < m_Settings.m_GridSize; x++)
	{
		for (int y = 0; y < m_Settings.m_GridSize; y++)
		{
			m_GameBoard[x][y] = false;  // Set each cell to a dead state.
			m_NeighborCounts[x][y] = 0;  // Reset the neighbor count for each cell.
		}
	}

	// Reset game statistical counters.
	m_Settings.m_LivingCells = 0;
	m_Settings.m_Generations = 0;

	SetStatusText();  // Update the game's status bar.
	p_DrawingPanel->Refresh();  // Redraw the grid to show the cleared state.
}

// Calculates the number of live neighbors surrounding a given cell.
int MainWindow::CalculateNeighborCount(int x, int y)
{
	int livingNeighbors = 0;  // Counter for living neighbors.
	int gridSize = m_Settings.m_GridSize;  // Fetch the grid size from settings.

	// Loop over the surrounding cells.
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			// Skip the cell itself.
			if (i == 0 && j == 0)
			{
				continue;
			}

			int neighborX = x + i;
			int neighborY = y + j;

			// Handle wrap-around in toroidal mode.
			if (m_Settings.isToroidalMode)
			{
				neighborX = (neighborX + gridSize) % gridSize;
				neighborY = (neighborY + gridSize) % gridSize;
			}

			// Check boundary conditions if in finite mode.
			if (!m_Settings.isToroidalMode && (neighborX < 0 || neighborX >= gridSize || neighborY < 0 || neighborY >= gridSize))
			{
				continue;
			}

			// Count the live neighbor cells.
			if (m_GameBoard[neighborX][neighborY])
			{
				livingNeighbors++;
			}
		}
	}
	return livingNeighbors;
}

// Recalculates and updates the neighbor count for every cell.
void MainWindow::UpdateNeighborCounts()
{
	// Iterate through every cell in the grid.
	for (int x = 0; x < m_Settings.m_GridSize; x++)
	{
		for (int y = 0; y < m_Settings.m_GridSize; y++)
		{
			m_NeighborCounts[x][y] = CalculateNeighborCount(x, y);  // Update neighbor count for the current cell.
		}
	}
}

// Method to compute and set the next generation state for the game.
void MainWindow::NextGeneration()
{
	std::vector<std::vector<bool>> sandbox(m_Settings.m_GridSize, std::vector<bool>(m_Settings.m_GridSize, false)); // Temporary grid to hold the state of the next generation.
	int livingCells = 0;  // Counter to keep track of living cells in the next generation.

	// Iterate through each cell in the current grid.
	for (int x = 0; x < m_Settings.m_GridSize; x++)
	{
		for (int y = 0; y < m_Settings.m_GridSize; y++)
		{
			int neighborCount = CalculateNeighborCount(x, y);  // Calculate the number of living neighbors for the current cell.

			// Check if the current cell is alive and has 2 or 3 neighbors.
			if (m_GameBoard[x][y] && (neighborCount == 2 || neighborCount == 3))
			{
				sandbox[x][y] = true;  // Cell remains alive in the next generation.
				livingCells++;  // Increment the living cells count.
			}
			// Check if the current cell is dead and has exactly 3 neighbors.
			else if (!m_GameBoard[x][y] && neighborCount == 3)
			{
				sandbox[x][y] = true;  // Cell becomes alive in the next generation.
				livingCells++;  // Increment the living cells count.
			}
			// Cells that don't meet the above conditions will remain or become dead in the sandbox.
		}
	}

	m_GameBoard.swap(sandbox);  // Replace the current game board with the next generation.
	UpdateNeighborCounts();  // Recalculate the neighbor counts for the new board.
	m_Settings.m_Generations++;  // Increment the generation count.
	m_Settings.m_LivingCells = livingCells;  // Update the living cells count.
	SetStatusText();  // Update the status text.
	p_DrawingPanel->Refresh();  // Refresh the drawing panel to reflect the new state.
}

// Event handler that progresses the game state by one generation at each timer interval.
void MainWindow::OnTimerEvent(wxTimerEvent& event)
{
	NextGeneration();  // Move the game to its next generation state.
}

// Event handler for adjusting game settings through the options menu.
void MainWindow::OnSettingsMenuClick(wxCommandEvent& event)
{
	OptionsMenu optionsMenu(this, &m_Settings, p_DrawingPanel);  // Create the options menu dialog with current settings.

	// Check if the user confirms the changes in the options menu.
	if (optionsMenu.ShowModal() == wxID_OK)
	{
		InitializeGameBoard();  // Reset the game board with the updated settings.
		p_DrawingPanel->Refresh();  // Refresh the drawing panel to reflect the new settings.
	}
}

// Event handler for toggling the display of the neighbor count for each cell.
void MainWindow::OnShowNeighborCount(wxCommandEvent& event)
{
	m_Settings.SetShowNeighborCount(!m_Settings.GetShowNeighborCount()); // Toggle the setting that determines whether or not to show the neighbor count.
	p_ViewMenu->Check(ToggleNeighborDisplayID, m_Settings.GetShowNeighborCount()); // Update the checkbox state of the corresponding menu item.
	p_DrawingPanel->Refresh(); // Redraw the drawing panel to reflect the changed setting.
}

// Handles mouse click events to change the state of cells in the game grid.
void MainWindow::OnMouseClick(wxMouseEvent& event)
{
	int MouseX = event.GetX();  // Obtain the x coordinate of the mouse click.
	int MouseY = event.GetY();  // Obtain the y coordinate of the mouse click.

	float CellWidth = p_DrawingPanel->GetSize().x / (float)m_Settings.m_GridSize;  // Compute the pixel width of each cell.
	float CellHeight = p_DrawingPanel->GetSize().y / (float)m_Settings.m_GridSize;  // Compute the pixel height of each cell.

	int ColumnX = MouseX / CellWidth;  // Determine the grid column of the click.
	int RowY = MouseY / CellHeight;  // Determine the grid row of the click.

	if (!m_GameBoard[RowY][ColumnX]) m_Settings.m_LivingCells++;  // If the cell is dead, increase living cells count.
	else m_Settings.m_LivingCells--;  // If the cell is alive, decrease living cells count.

	m_GameBoard[RowY][ColumnX] = !m_GameBoard[RowY][ColumnX];  // Toggle the cell's state.

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int newX = RowY + i;
			int newY = ColumnX + j;

			if (newX >= 0 && newX < m_Settings.m_GridSize && newY >= 0 && newY < m_Settings.m_GridSize)  // Ensure the cell is within the grid's boundaries.
			{
				m_NeighborCounts[newX][newY] = CalculateNeighborCount(newX, newY);  // Recalculate neighbor counts for this cell.
			}
		}
	}
	SetStatusText();  // Update the status text.
	Refresh();  // Redraw the main window to reflect changes.
}

// Event handler to start a new Game of Life session by clearing the board and the file path.
void MainWindow::OnNewClick(wxCommandEvent& event)
{
	OnClearButton(event);  // Clear the current game state.
	m_CurrentFilePath.clear();  // Clear the current file path since we're starting a new session.
}

// Reads a Game of Life pattern from a file and returns it as a 2D vector of booleans.
std::vector<std::vector<bool>> MainWindow::ReadPatternFromFile(const std::string& filePath)
{
	std::vector<std::vector<bool>> pattern;
	std::ifstream fileStream;
	std::string buffer;

	fileStream.open(filePath);  // Open the specified file for reading.
	if (fileStream.is_open())  // Check if the file stream was successfully opened.
	{
		while (std::getline(fileStream, buffer))  // Read the file line by line.
		{
			std::vector<bool> row(buffer.size());  // Initialize a new row for each line.

			for (int i = 0; i < buffer.size(); i++)  // Parse each character in the line.
			{
				row[i] = buffer[i] == '*';  // Assign true for '*' (alive) and false otherwise.
			}

			pattern.push_back(row);  // Add the parsed row to the pattern.
		}
		fileStream.close();  // Close the file after reading.
	}
	return pattern;  // Return the parsed pattern.
}

// Event handler to open an existing Game of Life file and load it into the application.
void MainWindow::OnFileOpenClick(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Open Game of Life File", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);  // Open a file selection dialog for loading game state.

	if (fileDialog.ShowModal() == wxID_CANCEL)  // Exit the method if user cancels the file dialog.
	{
		return;
	}

	m_GameBoard = ReadPatternFromFile(fileDialog.GetPath().ToStdString());  // Load the pattern from the selected file.
	m_CurrentFilePath = fileDialog.GetPath().ToStdString();  // Update the current file path to the selected file's path.

	m_Settings.m_GridSize = m_GameBoard.size();  // Set the grid size to match the loaded pattern.
	InitializeGameBoard();  // Reset and initialize the game board.
	UpdateNeighborCounts();  // Recalculate neighbor counts for the loaded pattern.
	p_DrawingPanel->Refresh();  // Refresh the drawing panel to display the loaded game state.
}

// Event handler to import a Game of Life pattern, centering it on the game board.
void MainWindow::OnFileImportClick(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Import Game of Life File", wxEmptyString, wxEmptyString, "Game of Life Files (*.cells) | *.cells", wxFD_OPEN);  // Open a file selection dialog for importing game state.

	if (fileDialog.ShowModal() == wxID_CANCEL)  // Exit the method if user cancels the file dialog.
	{
		return;
	}

	OnClearButton(event);  // Clear the current game state.
	m_CurrentFilePath.clear();  // Clear the current file path since we're importing a new game state.

	std::vector<std::vector<bool>> importedPattern = ReadPatternFromFile(fileDialog.GetPath().ToStdString());  // Import pattern from selected file.

	int minX = INT_MAX;
	int minY = INT_MAX;
	int maxX = 0;
	int maxY = 0;

	// Loop to find the boundaries of the active cells in the imported pattern.
	for (int y = 0; y < importedPattern.size(); y++)
	{
		for (int x = 0; x < importedPattern[y].size(); x++)
		{
			if (importedPattern[y][x])  // Check if cell at (x, y) is alive.
			{
				minX = std::min(minX, x);
				minY = std::min(minY, y);
				maxX = std::max(maxX, x);
				maxY = std::max(maxY, y);
			}
		}
	}

	int patternWidth = maxX - minX + 1;  // Compute the width of the alive cells' bounding box.
	int patternHeight = maxY - minY + 1;  // Compute the height of the alive cells' bounding box.

	// Calculate offsets to center the pattern on the game board.
	int xOffset = (m_Settings.m_GridSize - patternWidth) / 2 - minX;
	int yOffset = (m_Settings.m_GridSize - patternHeight) / 2 - minY;

	// Loop to place the imported pattern centered on the game board.
	for (int y = 0; y < importedPattern.size(); y++)
	{
		for (int x = 0; x < importedPattern[y].size(); x++)
		{
			int targetX = x + xOffset;
			int targetY = y + yOffset;

			// Check if the target cell position is within the game board boundaries.
			if (targetX >= 0 && targetX < m_Settings.m_GridSize &&
				targetY >= 0 && targetY < m_Settings.m_GridSize)
			{
				m_GameBoard[targetY][targetX] = importedPattern[y][x];  // Copy the cell state to the game board.
			}
		}
	}

	UpdateNeighborCounts();  // Recalculate neighbor counts after importing the new pattern.
	p_DrawingPanel->Refresh();  // Refresh the drawing panel to display the new game state.
}

// Saves the current game state to a file, representing alive cells with '*' and dead cells with '.'.
void MainWindow::SaveGameStateToFile(const std::string& path)
{
	std::ofstream fileStream(path);  // Open a file stream to the specified path for writing.

	if (fileStream.is_open())  // Check if the file stream was successfully opened.
	{
		// Iterate over the game board and write each cell's state to the file.
		for (int x = 0; x < m_Settings.m_GridSize; x++)
		{
			for (int y = 0; y < m_Settings.m_GridSize; y++)
			{
				fileStream << (m_GameBoard[x][y] ? '*' : '.');  // Write '*' for alive cells and '.' for dead cells.
			}
			fileStream << '\n';  // Insert a newline after each row.
		}
		fileStream.close();  // Close the file stream after saving the game state.
	}
}

// Event handler that saves the current game state.
// If a file path for the game state is not already set, prompts the user to provide one.
void MainWindow::OnFileSaveClick(wxCommandEvent& event)
{
	if (m_CurrentFilePath.empty())
	{
		OnFileSaveAsClick(event);				// If no current file path is known, trigger the "Save As" dialog.
	}
	else
	{
		SaveGameStateToFile(m_CurrentFilePath);	// Save the current game state to the already defined file path.
	}
}

// Event handler for "Save As" functionality.
// Allows the user to specify a new file location to save the current game state.
void MainWindow::OnFileSaveAsClick(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Save Game of Life File", wxEmptyString, wxEmptyString, 
		"Game of Life Files (*.cells) | *.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);	// Create and configure a file dialog for saving files.
	if (fileDialog.ShowModal() == wxID_CANCEL)	// Show the file dialog. If the user cancels the dialog, exit without saving.
	{
		return;
	}

	// Update the current file path with the one chosen by the user.
	m_CurrentFilePath = fileDialog.GetPath().ToStdString();

	// Save the game state to the chosen file path.
	SaveGameStateToFile(m_CurrentFilePath);
}

// Event handler that closes the application when the exit option is chosen.
void MainWindow::OnExitClick(wxCommandEvent& event)
{
	Close();	// Close the main window, which will trigger application shutdown.
}

// Handler for resetting settings to default values. Also updates the UI components accordingly.
void MainWindow::OnResetToDefaultClick(wxCommandEvent& event)
{
	m_Settings.ResetToDefault();					// Reset settings to default values.
	p_ViewMenu->Check(ToggleNeighborDisplayID, m_Settings.GetShowNeighborCount());  // Update the view menu based on the new settings.
	p_ViewMenu->Check(MenuViewShowGridID, m_Settings.GetShowGrid());	// Update the view menu based on the new settings.
	p_ViewMenu->Check(MenuViewShowHUDID, m_Settings.GetShowHUD());		// Update the view menu based on the new settings.
	OnClearButton(event);							// Clear the game board.
}

// Handler for switching to Finite mode and updating the UI components to reflect the change.
void MainWindow::OnFiniteMenuClick(wxCommandEvent& event)
{
	m_Settings.isToroidalMode = false;				// Set game mode to Finite.
	p_ViewMenu->Check(MenuViewFiniteID, true);		// Mark Finite mode as selected in the view menu.
	p_ViewMenu->Check(MenuViewToroidalID, false);	// Deselect Toroidal mode in the view menu.
	p_DrawingPanel->Refresh();						// Refresh the drawing panel to reflect the changes.
}

// Handler for switching to Toroidal mode and updating the UI components to reflect the change.
void MainWindow::OnToroidalMenuClick(wxCommandEvent& event)
{
	m_Settings.isToroidalMode = true;				// Set game mode to Toroidal.
	p_ViewMenu->Check(MenuViewToroidalID, true);	// Mark Toroidal mode as selected in the view menu.
	p_ViewMenu->Check(MenuViewFiniteID, false);		// Deselect Finite mode in the view menu.
	p_DrawingPanel->Refresh();						// Refresh the drawing panel to reflect the changes.
}

// Handler for toggling the visibility of the grid based on the user's selection.
void MainWindow::OnToggleShowGrid(wxCommandEvent& event)
{
	m_Settings.SetShowGrid(event.IsChecked());  // Update the settings to reflect the grid's visibility status.
	p_DrawingPanel->Refresh();					// Refresh the drawing panel to apply the changes.
}

// Handler for toggling the visibility of the 10x10 grid based on the user's selection.
void MainWindow::OnToggleShow10x10Grid(wxCommandEvent& event)
{
	m_Settings.SetShow10x10Grid(event.IsChecked());		// Update the settings to reflect the 10x10 grid's visibility status.
	p_DrawingPanel->Refresh();							// Refresh the drawing panel to apply the changes.
}

// Handler for toggling the visibility of the HUD (Heads-Up Display) based on the user's selection.
void MainWindow::OnToggleShowHUD(wxCommandEvent& event)
{
	m_Settings.SetShowHUD(event.IsChecked());	// Update the settings to reflect the HUD's visibility status.
	p_DrawingPanel->Refresh();					// Refresh the drawing panel to apply the changes.
}


// Notes
// naming conventions
// public no prefix
// private m for member prefix
// pointer p prefix
// & r for reference prefix
// functions often say get or set or have verbs
// buttonclicks event types have on prefix
// bool uses has prefix
