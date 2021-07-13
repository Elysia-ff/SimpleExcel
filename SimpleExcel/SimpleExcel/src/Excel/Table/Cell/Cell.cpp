#include "Cell.h"

Cell::Cell(const Table* _table)
	: table(_table)
	, tableRow(-1)
	, tableCol(-1)
{
}

std::istream& operator>>(std::istream& is, Cell::Type& cellType)
{
	unsigned char v;
	is >> v;

	cellType = static_cast<Cell::Type>(v);

	return is;
}
