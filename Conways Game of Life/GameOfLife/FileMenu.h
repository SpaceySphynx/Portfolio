#pragma once
#include "wx/wx.h"
#include "Settings.h"
#include <vector>
#include <string>

class FileMenu : public wxDialog
{
public:
	FileMenu();

	~FileMenu();

	static std::vector<std::string> ReadCellsFile(const std::string& filename);

	static void WriteCellsFile(const std::string& filename, const std::vector<std::string>& lines);

	std::string OpenFileDialog(wxWindow* parent, const wxString& defaultMessage, const wxString& defaultDir, const wxString& defaultFile, const wxString& wildcard, long style);

	std::string SaveFileDialog(wxWindow* parent, const wxString& defaultMessage, const wxString& defaultDir, const wxString& defaultFile, const wxString& wildcard, long style);

private:

};

