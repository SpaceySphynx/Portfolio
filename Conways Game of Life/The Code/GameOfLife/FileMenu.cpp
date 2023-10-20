#include "FileMenu.h"
#include <fstream>

FileMenu::FileMenu() 
{

}

FileMenu::~FileMenu()
{

}

std::vector<std::string> FileMenu::ReadCellsFile(const std::string& filename) 
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;

    if (file.is_open()) 
    {
        while (std::getline(file, line)) 
        {
            if (line.empty() || line[0] == '!') continue; // Skip comments or empty lines
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

void FileMenu::WriteCellsFile(const std::string& filename, const std::vector<std::string>& lines) 
{
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << std::endl;
        }
        file.close();
    }
}

// Additional helper function: Open file dialog and return selected filename
std::string FileMenu::OpenFileDialog(wxWindow* parent, const wxString& defaultMessage, const wxString& defaultDir, const wxString& defaultFile, const wxString& wildcard, long style) 
{
    wxFileDialog openFileDialog(parent, defaultMessage, defaultDir, defaultFile, wildcard, style);
    if (openFileDialog.ShowModal() == wxID_OK) 
    {
        return openFileDialog.GetPath().ToStdString();
    }
    return ""; // Return an empty string if user cancels or an error occurs
}

// Additional helper function: Save file dialog and return selected filename
std::string FileMenu::SaveFileDialog(wxWindow* parent, const wxString& defaultMessage, const wxString& defaultDir, const wxString& defaultFile, const wxString& wildcard, long style) 
{
    wxFileDialog saveFileDialog(parent, defaultMessage, defaultDir, defaultFile, wildcard, style);
    if (saveFileDialog.ShowModal() == wxID_OK) 
    {
        return saveFileDialog.GetPath().ToStdString();
    }
    return ""; // Return an empty string if user cancels or an error occurs
}