#include "StringCell.h"

StringCell::StringCell(const Table* _table, const std::string& _str)
	: Cell(_table)
	, str(_str)
{
}

StringCell::StringCell(const Table* _table, std::string&& _str)
	: Cell(_table)
	, str(std::move(_str))
{
}

Cell* StringCell::DeepCopy() const
{
	return new StringCell(*this);
}

std::string StringCell::ToString() const
{
	return str;
}

Int StringCell::ToInt() const
{
	return Int{ 0, EErrorCode::NONE };
}
