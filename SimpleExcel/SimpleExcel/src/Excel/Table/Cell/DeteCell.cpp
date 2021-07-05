#include "DateCell.h"

#include <cassert>
#include <ctime>

#include "Utility.hpp"

DateCell::DateCell(const Table* _table, const std::string& data)
	: Cell(_table)
{
	parse(data);
}

Cell* DateCell::DeepCopy() const
{
	return new DateCell(*this);
}

std::string DateCell::ToString() const
{
	std::string result;
	result.reserve(10);

	result.append(std::to_string(year));
	result.append(1, '-');
	if (month < 10)
	{
		result.append(1, '0');
	}
	result.append(std::to_string(month));
	result.append(1, '-');
	if (day < 10)
	{
		result.append(1, '0');
	}
	result.append(std::to_string(day));

	return result;
}

Int DateCell::ToInt() const
{
	tm t{ 0, };
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;

	time_t time = mktime(&t);

	return Int{ static_cast<int>(time), EErrorCode::NONE };
}

void DateCell::parse(const std::string& str)
{
	assert(Utility::IsDateForm(str));

	year = atoi(str.c_str());
	month = atoi(str.c_str() + 5);
	day = atoi(str.c_str() + 8);
}
