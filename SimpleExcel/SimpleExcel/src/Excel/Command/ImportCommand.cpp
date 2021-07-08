#include "ImportCommand.h"

#include <cassert>
#include <fstream>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Excel/Table/Cell/Cell.h"
#include "Excel/Table/Cell/StringCell.h"
#include "Excel/Table/Cell/NumberCell.h"
#include "Excel/Table/Cell/DateCell.h"
#include "Excel/Table/Cell/ExprCell.h"
#include "Utility.hpp"

bool ImportCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	std::string path;
	ss.ignore(); // remove ' '
	std::getline(ss, path);

	if (Utility::IsValidStream(ss) &&
		path.size() > 0)
	{
		std::string extension = Utility::GetExtension(path);
		auto iter = ImportFuncs.find(extension);
		if (iter == ImportFuncs.end())
		{
			excel->QueueMessage(UNSUPPORTED_EXT);

			return false;
		}

		std::ifstream input(path);
		if (!input.is_open())
		{
			excel->QueueMessage(FILE_OPEN_ERROR);

			return false;
		}

		bool bSucceded = (this->*iter->second)(excel, input);
		input.close();

		if (bSucceded)
		{
			return true;
		}

		excel->QueueMessage(IMPORT_FAILED);
	}

	return false;
}

bool ImportCommand::importAsSE(Excel* excel, std::ifstream& file) const
{
	std::string version;
	std::getline(file, version);

	std::string rowStr;
	std::getline(file, rowStr);
	int row = atoi(rowStr.c_str());
	if (row <= 0 || row > Table::ROW_LIMIT)
	{
		return false;
	}

	std::string colStr;
	std::getline(file, colStr);
	int col = atoi(colStr.c_str());
	if (col <= 0 || row > Table::COL_LIMIT)
	{
		return false;
	}

	Table* newTable = new Table(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			std::string line;
			std::getline(file, line);

			if (line.size() > 0)
			{
				std::stringstream ss(line);
				Cell::Type cellType;
				ss >> cellType;
				ss.ignore(); // remove ' '

				auto iter = AddFuncs.find(cellType);
				if (iter == AddFuncs.end() || !(this->*iter->second)(ss, newTable, i, k))
				{
					delete newTable;

					return false;
				}
			}
		}
	}

	if (excel->table)
	{
		delete excel->table;
	}

	excel->table = newTable;

	return true;
}

bool ImportCommand::addStringCell(std::stringstream& ss, Table* table, int row, int col) const
{
	assert(table);

	std::string str;
	std::getline(ss, str);

	table->Set(new StringCell(table, str), row, col);

	return true;
}

bool ImportCommand::addNumberCell(std::stringstream& ss, Table* table, int row, int col) const
{
	assert(table);

	int num;
	ss >> num;

	table->Set(new NumberCell(table, num), row, col);

	return true;
}

bool ImportCommand::addDateCell(std::stringstream& ss, Table* table, int row, int col) const
{
	assert(table);

	std::string date;
	ss >> date;

	if (Utility::IsDateForm(date))
	{
		table->Set(new DateCell(table, date), row, col);
		
		return true;
	}

	return false;
}

bool ImportCommand::addExprCell(std::stringstream& ss, Table* table, int row, int col) const
{
	assert(table);

	std::string expr;
	std::getline(ss, expr);

	table->Set(new ExprCell(table, expr), row, col);

	return true;
}
