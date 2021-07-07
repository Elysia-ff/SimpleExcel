#pragma once

#include <fstream>

#include "Excel/Command/ICommand.h"

class ExportCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;

private:
	inline static const std::string FILE_OPEN_ERROR = "Could not found the given path.";

	inline static const std::string FILE_SAVED = "File saved.";
};
