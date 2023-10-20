#pragma once
#include "wx/wx.h"
#include <fstream>

// Struct to store the settings for the game's parameters.
struct Settings
{
    // ---------------------- Default values ----------------------
    static const int DEFAULT_GRID_SIZE = 15;
    static const int DEFAULT_GENERATIONS = 0;
    static const int DEFAULT_LIVING_CELLS = 0;
    static const int DEFAULT_MILLISECONDS_TIL_NEXT_GENERATION = 50;
    static const int DEFAULT_ICON_WIDTH = 30;
    static const int DEFAULT_ICON_HEIGHT = 30;
    static const bool DEFAULT_SHOW_NEIGHBOR_COUNT = true;
    static const int DEFAULT_LIVING_RED = 128;
    static const int DEFAULT_LIVING_GREEN = 128;
    static const int DEFAULT_LIVING_BLUE = 128;
    static const int DEFAULT_LIVING_ALPHA = 255;
    static const int DEFAULT_DEAD_RED = 255;
    static const int DEFAULT_DEAD_GREEN = 255;
    static const int DEFAULT_DEAD_BLUE = 255;
    static const int DEFAULT_DEAD_ALPHA = 255;
    static const bool DEFAULT_SHOW_GRID = true;
    static const bool DEFAULT_SHOW_10x10_GRID = false;
    static const bool DEFAULT_SHOW_HUD = true;
    static const bool DEFAULT_IS_TOROIDAL_MODE = false;

    // ---------------------- Game Settings ----------------------
    int m_GridSize = DEFAULT_GRID_SIZE;
    int m_Generations = DEFAULT_GENERATIONS;
    int m_LivingCells = DEFAULT_LIVING_CELLS;
    int m_MillisecondsTilNextGeneration = DEFAULT_MILLISECONDS_TIL_NEXT_GENERATION;
    int m_IconWidth = DEFAULT_ICON_WIDTH;
    int m_IconHeight = DEFAULT_ICON_HEIGHT;
    bool m_ShowNeighborCount = DEFAULT_SHOW_NEIGHBOR_COUNT;
    bool m_ShowGrid = DEFAULT_SHOW_GRID;
    bool m_Show10x10Grid = DEFAULT_SHOW_10x10_GRID;
    bool m_ShowHUD = DEFAULT_SHOW_HUD;
    bool isToroidalMode = DEFAULT_IS_TOROIDAL_MODE;

    // RGBa values for living cell color.
    unsigned int m_LivingRed = DEFAULT_LIVING_RED;
    unsigned int m_LivingGreen = DEFAULT_LIVING_GREEN;
    unsigned int m_LivingBlue = DEFAULT_LIVING_BLUE;
    unsigned int m_LivingAlpha = DEFAULT_LIVING_ALPHA;

    // RGBa values for dead cell color.
    unsigned int m_DeadRed = DEFAULT_DEAD_RED;
    unsigned int m_DeadGreen = DEFAULT_DEAD_GREEN;
    unsigned int m_DeadBlue = DEFAULT_DEAD_BLUE;
    unsigned int m_DeadAlpha = DEFAULT_DEAD_ALPHA;

    // ---------------------- Color Manipulation Methods ----------------------
    void SetLivingColor(wxColor color)
    {
        m_LivingRed = color.GetRed();
        m_LivingGreen = color.GetGreen();
        m_LivingBlue = color.GetBlue();
        m_LivingAlpha = color.GetAlpha();
    }

    wxColor GetLivingColor() const
    {
        return wxColor(m_LivingRed, m_LivingGreen, m_LivingBlue, m_LivingAlpha);
    }

    void SetDeadColor(wxColor color)
    {
        m_DeadRed = color.GetRed();
        m_DeadGreen = color.GetGreen();
        m_DeadBlue = color.GetBlue();
        m_DeadAlpha = color.GetAlpha();
    }

    wxColor GetDeadColor() const
    {
        return wxColor(m_DeadRed, m_DeadGreen, m_DeadBlue, m_DeadAlpha);
    }

    // ---------------------- Settings I/O Methods ----------------------
    void SaveSettings()
    {
        std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
        file.write((char*)this, sizeof(Settings));
        file.close();
    }

    void LoadSettings()
    {
        std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
        file.read((char*)this, sizeof(Settings));
        file.close();
    }

    // ---------------------- Setter/Getter Methods ----------------------
    bool GetShowNeighborCount() { return m_ShowNeighborCount; }
    void SetShowNeighborCount(bool show) { m_ShowNeighborCount = show; }

    bool GetShowGrid() const { return m_ShowGrid; }
    void SetShowGrid(bool show) { m_ShowGrid = show; }

    bool GetShow10x10Grid() const { return m_Show10x10Grid; }
    void SetShow10x10Grid(bool show) { m_Show10x10Grid = show; }

    bool GetShowHUD() const { return m_ShowHUD; }
    void SetShowHUD(bool show) { m_ShowHUD = show; }

    void ResetToDefault()
    {
        m_GridSize = DEFAULT_GRID_SIZE;
        m_Generations = DEFAULT_GENERATIONS;
        m_LivingCells = DEFAULT_LIVING_CELLS;
        m_MillisecondsTilNextGeneration = DEFAULT_MILLISECONDS_TIL_NEXT_GENERATION;
        m_IconWidth = DEFAULT_ICON_WIDTH;
        m_IconHeight = DEFAULT_ICON_HEIGHT;
        m_ShowNeighborCount = DEFAULT_SHOW_NEIGHBOR_COUNT;
        m_LivingRed = DEFAULT_LIVING_RED;
        m_LivingGreen = DEFAULT_LIVING_GREEN;
        m_LivingBlue = DEFAULT_LIVING_BLUE;
        m_LivingAlpha = DEFAULT_LIVING_ALPHA;
        m_DeadRed = DEFAULT_DEAD_RED;
        m_DeadGreen = DEFAULT_DEAD_GREEN;
        m_DeadBlue = DEFAULT_DEAD_BLUE;
        m_DeadAlpha = DEFAULT_DEAD_ALPHA;
        m_ShowGrid = DEFAULT_SHOW_GRID;
        m_Show10x10Grid = DEFAULT_SHOW_10x10_GRID;
        m_ShowHUD = DEFAULT_SHOW_HUD;
        isToroidalMode = DEFAULT_IS_TOROIDAL_MODE;
    }
};

