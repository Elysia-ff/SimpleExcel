#pragma once

#include <unordered_map>
#include <sstream>

#include "Excel/Command/ICommand.h"
#include "Excel/Table/Cell/Cell.h"

class Table;

class ImportCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;

private:
	bool importAsSE(Excel* excel, std::ifstream& file) const;

	bool addStringCell(std::stringstream& ss, Table* table, int row, int col) const;

	bool addNumberCell(std::stringstream& ss, Table* table, int row, int col) const;

	bool addDateCell(std::stringstream& ss, Table* table, int row, int col) const;

	bool addExprCell(std::stringstream& ss, Table* table, int row, int col) const;

private:
	inline static const std::string FILE_OPEN_ERROR = "Could not found the given path.";

	inline static const std::string UNSUPPORTED_EXT = "Unsupported extension.";

	inline static const std::string IMPORT_FAILED = "Import failed.";

	std::unordered_map<std::string, bool (ImportCommand::*)(Excel* excel, std::ifstream& file) const> ImportFuncs
	{
		{ "se", &ImportCommand::importAsSE },
	};

	std::unordered_map<Cell::Type, bool (ImportCommand::*)(std::stringstream& ss, Table* table, int row, int col) const> AddFuncs
	{
		{ Cell::Type::String, &ImportCommand::addStringCell },
		{ Cell::Type::Number, &ImportCommand::addNumberCell },
		{ Cell::Type::Date, &ImportCommand::addDateCell },
		{ Cell::Type::Expr, &ImportCommand::addExprCell },
	};
};
