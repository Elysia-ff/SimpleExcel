#include "DateCell.h"

#include <cassert>
#include <ctime>

#include "Utility.hpp"

DateCell::DateCell(const std::string& _data)
	: Cell(_data)
{
	assert(Utility::IsDateForm(ToString()));
}

DateCell::DateCell(std::string&& _data)
	: Cell(std::move(_data))
{
	assert(Utility::IsDateForm(ToString()));
}

Cell* DateCell::DeepCopy() const
{
	return new DateCell(*this);
}

int DateCell::ToInt() const
{
	const std::string& date = ToString();

	tm t{ 0, };
	t.tm_year = atoi(date.c_str()) - 1900;
	t.tm_mon = atoi(date.c_str() + 5) - 1;
	t.tm_mday = atoi(date.c_str() + 8);

	time_t time = mktime(&t);

	return static_cast<int>(time);
}
