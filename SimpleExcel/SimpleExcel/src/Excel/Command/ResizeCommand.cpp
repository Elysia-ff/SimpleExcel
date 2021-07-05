#include "ResizeCommand.h"

#include <cassert>
#include <cmath>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Excel/Table/Cell/Cell.h"
#include "Utility.hpp"

bool ResizeCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	int row;
	int col;
	ss >> row >> col;

	if (Utility::IsValidStream(ss) &&
		0 < row && row <= Table::ROW_LIMIT &&
		0 < col && col <= Table::COL_LIMIT)
	{
		Table* newTable = new Table(row, col);

		if (excel->table)
		{
			int maxRow = std::min(row, excel->table->GetMaxRow());
			int maxCol = std::min(col, excel->table->GetMaxCol());
			for (int i = 0; i < maxRow; i++)
			{
				for (int k = 0; k < maxCol; k++)
				{
					Cell* cell = excel->table->Get(i, k);
					if (cell)
					{
						newTable->Set(cell->DeepCopy(), i, k);
					}
				}
			}

			delete excel->table;
		}

		excel->table = newTable;

		return true;
	}

	return false;
}
