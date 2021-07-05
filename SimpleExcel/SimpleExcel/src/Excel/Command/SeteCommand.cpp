#include "SeteCommand.h"

#include <cassert>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Excel/Table/Cell/ExprCell.h"
#include "Utility.hpp"

bool SeteCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	std::string cell;
	std::string expr;
	ss >> cell;
	ss.ignore(); // remove ' '
	std::getline(ss, expr);

	if (Utility::IsValidStream(ss) &&
		Utility::IsCell(cell) &&
		expr.size() > 0)
	{
		int row;
		int col;
		Utility::ParseRowCol(cell, &row, &col);

		if (excel->table &&
			0 <= row && row < excel->table->GetMaxRow() &&
			0 <= col && col < excel->table->GetMaxCol())
		{
			excel->table->Set(new ExprCell(excel->table, expr), row, col);

			return true;
		}
	}

	return false;
}
