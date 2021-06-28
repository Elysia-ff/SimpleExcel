#include "StringCell.h"

StringCell::StringCell(const std::string& _data)
	: Cell(_data)
{
}

StringCell::StringCell(std::string&& _data)
	: Cell(std::move(_data))
{
}

Cell* StringCell::DeepCopy() const
{
	return new StringCell(*this);
}

int StringCell::ToInt() const
{
	return 0;
}
