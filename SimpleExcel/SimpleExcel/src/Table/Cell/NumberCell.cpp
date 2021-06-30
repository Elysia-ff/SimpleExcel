#include "NumberCell.h"

#include <cmath>

NumberCell::NumberCell(const Table* _table, int _num)
	: Cell(_table)
	, num(_num)
{
}

Cell* NumberCell::DeepCopy() const
{
	return new NumberCell(*this);
}

std::string NumberCell::ToString() const
{
	return std::to_string(num);
}

Int NumberCell::ToInt() const
{
	return Int{ num, EErrorCode::NONE };
}
