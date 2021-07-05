#include "SetsCommand.h"

#include <cassert>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Excel/Table/Cell/StringCell.h"
#include "Utility.hpp"

bool SetsCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	std::string cell;
	std::string str;
	ss >> cell;
	ss.ignore(); // remove ' ';
	std::getline(ss, str);

	if (Utility::IsValidStream(ss) &&
		Utility::IsCell(cell) &&
		str.size() > 0)
	{
		int row;
		int col;
		Utility::ParseRowCol(cell, &row, &col);
		
		if (excel->table &&
			0 <= row && row < excel->table->GetMaxRow() &&
			0 <= col && col < excel->table->GetMaxCol())
		{
			excel->table->Set(new StringCell(excel->table, str), row, col);

			return true;
		}
	}

	return false;
}
