#include "DeleteCommand.h"

#include <cassert>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Utility.hpp"

bool DeleteCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	std::string param;
	ss >> param;

	if (Utility::IsValidStream(ss) &&
		param.size() > 0)
	{
		if (param == PARAM_ALL)
		{
			if (excel->table)
			{
				delete excel->table;
				excel->table = nullptr;
			}

			return true;
		}
		else if (Utility::IsCell(param))
		{
			int row;
			int col;
			Utility::ParseRowCol(param, &row, &col);

			if (excel->table &&
				0 <= row && row < excel->table->GetMaxRow() &&
				0 <= col && col < excel->table->GetMaxCol())
			{
				excel->table->Set(nullptr, row, col);

				return true;
			}
		}
	}

	return false;
}
