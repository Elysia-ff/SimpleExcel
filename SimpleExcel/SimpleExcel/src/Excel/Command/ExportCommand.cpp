#include "ExportCommand.h"

#include <cassert>
#include <fstream>

#include "Excel/Excel.h"
#include "Excel/Table/Table.h"
#include "Excel/Table/Cell/Cell.h"
#include "Utility.hpp"

bool ExportCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	std::string path;
	ss >> path;

	if (Utility::IsValidStream(ss) &&
		path.size() > 0)
	{
		std::ofstream output(path, std::ios::trunc);

		if (!output.is_open())
		{
			excel->QueueMessage(FILE_OPEN_ERROR);
			return false;
		}

		if (excel->table)
		{
			int row = excel->table->GetMaxRow();
			int col = excel->table->GetMaxCol();
			for (int i = 0; i < row; i++)
			{
				for (int k = 0; k < col; k++)
				{
					Cell* cell = excel->table->Get(i, k);
					if (cell)
					{
						output << cell->ToString();
					}

					if (k < col - 1)
					{
						output << ',';
					}
				}

				if (i < row - 1)
				{
					output << '\n';
				}
			}
		}

		output.close();
		excel->QueueMessage(FILE_SAVED);

		return true;
	}

	return false;
}
