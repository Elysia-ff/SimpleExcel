#include "NumberCell.h"

#include <cmath>

NumberCell::NumberCell(int _data)
	: Cell(std::to_string(_data))
{
}

Cell* NumberCell::DeepCopy() const
{
	return new NumberCell(*this);
}

int NumberCell::ToInt() const
{
	const std::string& str = ToString();
	int result = 0;
	int digit = 1;

	for (auto iter = str.rbegin(); iter != str.rend(); ++iter)
	{
		int c = *iter - '0';

		result += c * digit;
		digit *= 10;
	}

	return result;
}
