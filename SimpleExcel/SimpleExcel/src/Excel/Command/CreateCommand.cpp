#include "CreateCommand.h"

#include <cassert>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Utility.hpp"

bool CreateCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	int row;
	int col;
	ss >> row >> col;

	if (Utility::IsValidStream(ss) &&
		0 < row && row <= Table::ROW_LIMIT &&
		0 < col && col <= Table::COL_LIMIT)
	{
		if (excel->table)
		{
			delete excel->table;
		}

		excel->table = new Table(row, col);

		return true;
	}

	return false;
}
