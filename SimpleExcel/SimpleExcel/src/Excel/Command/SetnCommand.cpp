#include "SetnCommand.h"

#include <cassert>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Excel/Table/Cell/NumberCell.h"
#include "Utility.hpp"

bool SetnCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	std::string cell;
	int num;
	ss >> cell >> num;

	if (Utility::IsValidStream(ss) &&
		Utility::IsCell(cell))
	{
		int row;
		int col;
		Utility::ParseRowCol(cell, &row, &col);

		if (excel->table &&
			0 <= row && row < excel->table->GetMaxRow() &&
			0 <= col && col < excel->table->GetMaxCol())
		{
			excel->table->Set(new NumberCell(excel->table, num), row, col);

			return true;
		}
	}

	return false;
}
