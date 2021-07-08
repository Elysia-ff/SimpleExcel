#pragma once

#include <fstream>
#include <unordered_map>

#include "Excel/Command/ICommand.h"

class ExportCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;

private:
	void exportAsCSV(Excel* excel, std::ofstream& file) const;

	void exportAsSE(Excel* excel, std::ofstream& file) const;

private:
	inline static const std::string FILE_OPEN_ERROR = "Could not found the given path.";

	inline static const std::string FILE_SAVED = "File saved.";

	inline static const std::string UNSUPPORTED_EXT = "Unsupported extension.";

	std::unordered_map<std::string, void (ExportCommand::*)(Excel* excel, std::ofstream& file) const> ExportFuncs
	{
		{ "csv", &ExportCommand::exportAsCSV },
		{ "se", &ExportCommand::exportAsSE },
	};
};
