#pragma once
#include "wx/wx.h"
#include "Settings.h"

class MainWindow;	// Forward declaration used to prevent cyclic dependencies.
class DrawingPanel : public wxPanel	// DrawingPanel with wxPanel where the state of the Game of Life is visualized.
{
public:
	DrawingPanel(wxFrame* parent, wxSize size, std::vector<std::vector<bool>>& gameBoard,	// Constructor: Initializes the DrawingPanel with a parent window, 
		std::vector<std::vector<int>>& neighborCounts);										// its size, references to the game board and the neighbor counts of each cell.

	~DrawingPanel();	// Destructor

	std::function<void()> setstatustext;							// required to access function outside of DrawingPanel in MainWindow.
	
	void SetGridSize(int size);										// Set the dimensions (both width and height) of the grid.
	void SetSettings(Settings* settings);							// Method to associate settings with the DrawingPanel.
	void RandomizeGrid(int seed = -1);								// Randomly set cells to alive or dead state, with an optional seed.
	void CallSetStatusText(const std::function<void()>& callback);	// Callback function to access SetStatusText method in MainWindow.
	wxDECLARE_EVENT_TABLE();										// Macro to declare methods for the event table.

private:
	Settings* m_Settings = nullptr;									// Pointer to the game settings set to nullptr to avoid uninitialized pointers.

	std::vector<std::vector<bool>>& m_GameBoardReference;			// Reference to the game board, which represents the current state of each cell.
	std::vector<std::vector<int>>& m_NeighborCounts;				// Reference to the neighbor counts of each cell.
	int CountNeighbors(int x, int y);								// Given a cell's position, count and return the number of living neighbors around it.

	void OnPaint(wxPaintEvent& event);								// Handles drawing the state of the game on this panel.
	void DrawHUD(wxDC& dc);
};

