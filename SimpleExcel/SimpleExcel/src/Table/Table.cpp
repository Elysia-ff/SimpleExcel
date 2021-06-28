#include "Table.h"

#include "Cell/Cell.h"

Table::Table(int row, int col)
	: maxRow(row)
	, maxCol(col)
{
	assert(0 < row && row < ROW_LIMIT);
	assert(0 < col && col < COL_LIMIT);

	cells = new Cell * *[maxRow];
	for (int i = 0; i < maxRow; i++)
	{
		cells[i] = new Cell * [maxCol] { 0, };
	}
}

Table::Table(const Table& source)
	: maxRow(source.maxRow)
	, maxCol(source.maxCol)
{
	cells = new Cell * *[maxRow];
	for (int i = 0; i < maxRow; i++)
	{
		cells[i] = new Cell * [maxCol] { 0, };
		for (int k = 0; k < maxCol; k++)
		{
			if (source.cells[i][k] != nullptr)
			{
				cells[i][k] = source.cells[i][k]->DeepCopy();
			}
		}
	}
}

Table::Table(Table&& source) noexcept
	: cells(source.cells)
	, maxRow(source.maxRow)
	, maxCol(source.maxCol)
{
	source.cells = nullptr;
	source.maxRow = 0;
	source.maxCol = 0;
}

Table::~Table()
{
	releaseMemory();
}

Table& Table::operator=(const Table& source)
{
	if (this != &source)
	{
		releaseMemory();

		maxRow = source.maxRow;
		maxCol = source.maxCol;

		cells = new Cell * *[maxRow];
		for (int i = 0; i < maxRow; i++)
		{
			cells[i] = new Cell * [maxCol] { 0, };
			for (int k = 0; k < maxCol; k++)
			{
				if (source.cells[i][k] != nullptr)
				{
					cells[i][k] = source.cells[i][k]->DeepCopy();
				}
			}
		}
	}

	return *this;
}

Table& Table::operator=(Table&& source) noexcept
{
	if (this != &source)
	{
		releaseMemory();

		cells = source.cells;
		maxRow = source.maxRow;
		maxCol = source.maxCol;

		source.cells = nullptr;
		source.maxRow = 0;
		source.maxCol = 0;
	}

	return *this;
}

void Table::Set(Cell* cell, int row, int col)
{
	assert(cells);
	assert(0 <= row && row < maxRow);
	assert(0 <= col && col < maxCol);

	if (cells[row][col] != nullptr)
	{
		delete cells[row][col];
	}

	cells[row][col] = cell;
}

std::string Table::ToString() const
{
	std::string result;

	int* colSize = new int[maxCol]{ 0, };
	int rowHeaderSize = static_cast<int>(rowToString(maxRow - 1).size());

	// Col Header
	result.append(rowHeaderSize, ' ');
	result.append("  |");
	for (int k = 0; k < maxCol; k++)
	{
		result.append(1, ' ');
		std::string header = colToString(k);
		result.append(header);

		colSize[k] = static_cast<int>(header.size());
		for (int i = 0; i < maxRow; i++)
		{
			int size = getCellSize(i, k);
			if (colSize[k] < size)
			{
				colSize[k] = size;
			}
		}

		result.append(colSize[k] - header.size(), ' ');
		result.append(" |");
	}
	//

	std::string lineStr;
	lineStr.reserve(result.size() + 2);
	lineStr.append(1, '\n');
	lineStr.append(result.size(), '-');
	lineStr.append(1, '\n');
	result.append(lineStr);

	for (int i = 0; i < maxRow; i++)
	{
		// Row Header
		result.append(1, ' ');
		std::string header = rowToString(i);
		result.append(header);
		result.append(rowHeaderSize - header.size(), ' ');
		result.append(" |");
		//

		for (int k = 0; k < maxCol; k++)
		{
			result.append(1, ' ');
			if (cells[i][k] == nullptr)
			{
				result.append(colSize[k], ' ');
			}
			else
			{
				std::string str = cells[i][k]->ToString();
				result.append(str);
				result.append(colSize[k] - str.size(), ' ');
			}
			result.append(" |");
		}
		
		result.append(lineStr);
	}

	delete[] colSize;

	return result;
}

void Table::releaseMemory()
{
	if (cells)
	{
		for (int i = 0; i < maxRow; i++)
		{
			for (int k = 0; k < maxCol; k++)
			{
				if (cells[i][k] != nullptr)
				{
					delete cells[i][k];
				}
			}

			delete[] cells[i];
		}

		delete[] cells;

		cells = nullptr;
		maxRow = 0;
		maxCol = 0;
	}
}

int Table::getCellSize(int row, int col) const
{
	assert(cells);
	assert(0 <= row && row < maxRow);
	assert(0 <= col && col < maxCol);

	if (cells[row][col] != nullptr)
	{
		size_t size = cells[row][col]->ToString().size();

		return static_cast<int>(size);
	}

	return 0;
}
