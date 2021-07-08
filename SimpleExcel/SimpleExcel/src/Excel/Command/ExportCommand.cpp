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
	ss.ignore(); // remove ' '
	std::getline(ss, path);

	if (Utility::IsValidStream(ss) &&
		path.size() > 0)
	{
		std::string extension = Utility::GetExtension(path);
		auto iter = ExportFuncs.find(extension);
		if (iter == ExportFuncs.end())
		{
			excel->QueueMessage(UNSUPPORTED_EXT);

			return false;
		}

		std::ofstream output(path, std::ios::trunc);
		if (!output.is_open())
		{
			excel->QueueMessage(FILE_OPEN_ERROR);

			return false;
		}

		(this->*iter->second)(excel, output);
		output.close();
		excel->QueueMessage(FILE_SAVED);

		return true;
	}

	return false;
}

void ExportCommand::exportAsCSV(Excel* excel, std::ofstream& file) const
{
	if (excel->table == nullptr)
	{
		return;
	}

	int row = excel->table->GetMaxRow();
	int col = excel->table->GetMaxCol();
	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			Cell* cell = excel->table->Get(i, k);
			if (cell)
			{
				if (cell->GetType() == Cell::Type::String)
				{
					file << '\"';
					file << cell->ToString();
					file << '\"';
				}
				else
				{
					file << cell->ToString();
				}
			}

			if (k < col - 1)
			{
				file << ',';
			}
		}

		if (i < row - 1)
		{
			file << '\n';
		}
	}
}

void ExportCommand::exportAsSE(Excel* excel, std::ofstream& file) const
{
	if (excel->table == nullptr)
	{
		return;
	}

	file << Excel::VERSION << '\n';

	int row = excel->table->GetMaxRow();
	int col = excel->table->GetMaxCol();
	file << row << '\n' << col << '\n';

	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			Cell* cell = excel->table->Get(i, k);
			if (cell)
			{
				unsigned char code = static_cast<unsigned char>(cell->GetType());
				file << code << ' ' << cell->GetPlainText();
			}

			if (k < col - 1)
			{
				file << '\n';
			}
		}

		if (i < row - 1)
		{
			file << '\n';
		}
	}
}
