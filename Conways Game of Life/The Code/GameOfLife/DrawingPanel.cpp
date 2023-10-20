#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include <ctime>
#include <cstdlib>

// Event table mapping events to their respective handler functions.
wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()

// Constructor: Initializes the DrawingPanel with the provided size, game board, and neighbor counts.
DrawingPanel::DrawingPanel(wxFrame* parent, wxSize size, std::vector<std::vector<bool>>& gameBoard, std::vector<std::vector<int>>& neighborCounts)
    : wxPanel(parent, wxID_ANY, wxPoint(0, 0), size), m_GameBoardReference(gameBoard), m_NeighborCounts(neighborCounts)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);   // Use a paint-style background (better for redrawing).
    SetDoubleBuffered(true);                // Enable double buffering to reduce flickering.
}

// Destructor: Clean up resources related to the DrawingPanel.
DrawingPanel::~DrawingPanel()
{
    // Nothing to clean up for now.
}

// Function to draw the Heads-Up Display (HUD) on the drawing panel.
void DrawingPanel::DrawHUD(wxDC& dc)
{
    if (m_Settings->GetShowHUD())
    {
        // Set the text properties for the HUD display.
        dc.SetFont(wxFontInfo(16));
        dc.SetTextForeground(*wxRED);

        // Construct HUD text based on current game settings.
        wxString genText = "Generations: " + std::to_string(m_Settings->m_Generations);
        wxString aliveText = "Living Cells: " + std::to_string(m_Settings->m_LivingCells);
        wxString boundaryMode = m_Settings->isToroidalMode ? "Toroidal" : "Finite";
        wxString boundaryText = "Boundary: " + boundaryMode;
        wxString sizeText = "Universe Size: " + std::to_string(m_Settings->m_GridSize);

        wxCoord x, y;
        dc.GetTextExtent(genText, &x, &y);

        wxSize panelSize = GetSize();
        double panelWidth = panelSize.GetWidth();
        double panelHeight = panelSize.GetHeight();

        double offsetY = panelHeight - 4 * y; // Calculate the Y offset based on the text's height.

        // Render the HUD text at the computed positions.
        dc.DrawText(genText, 10, offsetY);
        dc.DrawText(aliveText, 10, offsetY + y);
        dc.DrawText(boundaryText, 10, offsetY + 2 * y);
        dc.DrawText(sizeText, 10, offsetY + 3 * y);
    }
}

// Handles the paint event for the drawing panel. It renders the game board, cells, grid, 
// neighbor counts, and HUD using the settings provided. Utilizes buffered drawing to reduce flickering.
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    // Initialize a buffered device context to reduce flicker during drawing.
    wxAutoBufferedPaintDC dc(this);
    // Clear the drawing canvas ensuring a clean slate for every paint event.
    dc.Clear();

    // Attempt to create a graphics context using the given device context.
    // Graphics context allows for advanced drawing operations.
    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context) return;  // If context creation fails, terminate drawing.

    // Compute the dimensions for each cell based on panel size and grid size.
    float CellWidth = (GetSize().x / (float)m_Settings->m_GridSize);
    float CellHeight = (GetSize().y / (float)m_Settings->m_GridSize);

    // Ensure that there are valid settings before drawing the board.
    if (m_Settings)
    {
        // Fetch the color settings for cells that are alive and dead.
        wxColor livingColor = m_Settings->GetLivingColor();
        wxColor deadColor = m_Settings->GetDeadColor();

        // Set the pen to transparent to avoid drawing rectangle borders.
        context->SetPen(*wxTRANSPARENT_PEN);

        // Traverse through the entire game grid to visualize each cell.
        for (int i = 0; i < m_Settings->m_GridSize; i++)
        {
            for (int j = 0; j < m_Settings->m_GridSize; j++)
            {
                // Set the brush color according to whether the cell is alive or dead.
                if (m_GameBoardReference[i][j])
                {
                    context->SetBrush(livingColor);
                }
                else
                {
                    context->SetBrush(deadColor);
                }

                // Render the cell as a filled rectangle.
                // The added +1 pixel prevents faint transparent gaps when the grid is turned off.
                context->DrawRectangle(CellWidth * j, CellHeight * i, CellWidth + 1, CellHeight + 1);

                // Check if the neighbor count is enabled and if the current cell has neighboring cells.
                if (i < m_NeighborCounts.size() && j < m_NeighborCounts[i].size() && m_Settings->GetShowNeighborCount() && m_NeighborCounts[i][j] > 0)
                {
                    wxString text = wxString::Format("%d", m_NeighborCounts[i][j]);

                    // Apply text properties for rendering.
                    context->SetFont(dc.GetFont(), *wxBLACK);
                    wxDouble textWidth, textHeight, descent, externalLeading;
                    context->GetTextExtent(text, &textWidth, &textHeight, &descent, &externalLeading);

                    // Calculate coordinates to center the neighbor count text within the cell.
                    wxDouble xPos = (CellWidth * j) + (CellWidth - textWidth) / 2;
                    wxDouble yPos = (CellHeight * i) + (CellHeight - textHeight) / 2;

                    // Overlay the cell with the neighbor count text.
                    context->DrawText(text, xPos, yPos);
                }
            }
        }

        // Restore the pen color to its default (black).
        context->SetPen(*wxBLACK);

        // Check if the regular grid display is turned on.
        if (m_Settings->m_ShowGrid)
        {
            wxPen transparentPen(wxColor(0, 0, 0, 64));  // Define a semi-transparent pen for the grid lines.
            dc.SetPen(transparentPen);

            // Overlay the board with regular grid lines.
            for (int i = 1; i < m_Settings->m_GridSize; i++)
            {
                dc.DrawLine(CellWidth * i, 0, CellWidth * i, GetSize().y);
                dc.DrawLine(0, CellHeight * i, GetSize().x, CellHeight * i);
            }
        }

        // Check if the 10x10 grid display is turned on.
        if (m_Settings->m_Show10x10Grid)
        {
            int solidLines = m_Settings->m_GridSize / 10;
            wxPen thickPen(*wxBLACK, 2);  // Define a thicker pen for the 10x10 grid lines.
            dc.SetPen(thickPen);

            // Overlay the board with the 10x10 grid lines.
            for (int i = 1; i <= solidLines; i++)
            {
                int linePosition = 10 * i;

                dc.DrawLine(CellWidth * linePosition, 0, CellWidth * linePosition, GetSize().y);
                dc.DrawLine(0, CellHeight * linePosition, GetSize().x, CellHeight * linePosition);
            }
        }
    }

    // Render the HUD (Heads-Up Display) on the panel.
    DrawHUD(dc);

    // Free up the memory allocated for the graphics context.
    delete context;
}

// Adjusts the grid size for the drawing panel and correspondingly resizes the game board 
// and neighbor counts matrices to match the specified size.
void DrawingPanel::SetGridSize(int size)
{
    m_Settings->m_GridSize = size;  // Update the grid size setting with the specified size.
    m_GameBoardReference.resize(m_Settings->m_GridSize);    // Resize the game board matrix to match the new grid size.
    for (auto& row : m_GameBoardReference) row.resize(m_Settings->m_GridSize);  // Resize each row.
    m_NeighborCounts.resize(m_Settings->m_GridSize);    // Resize the neighbor counts matrix to match the new grid size.
    for (auto& row : m_NeighborCounts) row.resize(m_Settings->m_GridSize);  // Resize each row.
}

// Assigns a Settings object to the DrawingPanel, enabling customization of 
// drawing parameters such as grid size and color schemes.
void DrawingPanel::SetSettings(Settings* settings)
{
    m_Settings = settings;  // Assign the provided settings object to the panel's settings member.
}

// Computes the number of living neighbors for a specific cell in the game board. 
// Neighbors are cells adjacent to the given cell, including diagonally adjacent cells.
int DrawingPanel::CountNeighbors(int x, int y)
{
    int count = 0;  // Initialize a counter for living neighbors.
    int gridSize = m_Settings->m_GridSize;  // Fetch the current grid size for boundary checks.

    // Traverse the 3x3 square around the specified cell (x, y).
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // Exclude the current cell from the count.
            if (i == 0 && j == 0) continue;

            // Calculate the coordinates of the neighboring cell.
            int newX = x + i;
            int newY = y + j;

            // Ensure that the neighbor's coordinates are within the game board boundaries.
            if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize)
            {
                // If the neighbor is alive, increment the count.
                count += m_GameBoardReference[newX][newY] ? 1 : 0;
            }
        }
    }
    return count;   // Return the total number of living neighbors.
}

// Populates the game board with a random configuration of living cells. 
// This can be based on a provided seed or use the current time for randomness. After the 
// grid is randomized, it updates the neighboring cells count and refreshes the game display.
void DrawingPanel::RandomizeGrid(int seed)
{
    // If no specific seed is provided, use the current time for randomness.
    if (seed == -1)
    {
        srand(static_cast<unsigned int>(time(NULL)));
    }
    else
    {
        srand(seed);  // Use the provided seed for reproducible randomness.
    }

    // Initialize the living cells count to zero before randomization.
    m_Settings->m_LivingCells = 0;

    // Traverse the entire grid.
    for (int i = 0; i < m_Settings->m_GridSize; i++)
    {
        for (int j = 0; j < m_Settings->m_GridSize; j++)
        {
            // Assign a random state (alive or dead) to the cell.
            m_GameBoardReference[i][j] = (rand() % 2 == 0);

            // Increment the living cells count if the cell is alive.
            if (m_GameBoardReference[i][j])
            {
                m_Settings->m_LivingCells++;
            }
        }
    }

    // After populating the grid, update the neighbor count for each cell.
    for (int i = 0; i < m_Settings->m_GridSize; i++)
    {
        for (int j = 0; j < m_Settings->m_GridSize; j++)
        {
            m_NeighborCounts[i][j] = CountNeighbors(i, j);
        }
    }

    // Update the status text and trigger a visual refresh of the game.
    setstatustext();
    Refresh();
}

// Assigns a callback function to update the status text in the MainWindow. 
// This allows the DrawingPanel to request a status text update without directly accessing 
// MainWindow methods.
void DrawingPanel::CallSetStatusText(const std::function<void()>& callback)
{
    setstatustext = callback;  // Assign the provided callback function to the member variable.
}
