#pragma once

#include <string>

class Utility
{
public:
	Utility() = delete;

	// YYYY-MM-DD 
	static bool IsDateForm(const std::string& str)
	{
		if (str.size() != 10)
		{
			return false;
		}

		if (str[4] != '-' || str[7] != '-')
		{
			return false;
		}

		int year = atoi(str.c_str());
		if (year < 1970)
		{
			return false;
		}

		int month = atoi(str.c_str() + 5);
		if (month < 1 || month > 12)
		{
			return false;
		}

		int day = atoi(str.c_str() + 8);
		if (day < 1)
		{
			return false;
		}

		int lastDay = 0;
		if (month == 2)
		{
			lastDay = IsLeapYear(year) ? 29 : 28;
		}
		else
		{
			int lastDayOfMonth[]{ 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			lastDay = lastDayOfMonth[month - 1];
		}

		if (day > lastDay)
		{
			return false;
		}

		return true;
	}

	static bool IsLeapYear(int year)
	{
		if (year % 4 == 0)
		{
			if (year % 100 == 0)
			{
				return year % 400 == 0;
			}
			
			return true;
		}

		return false;
	}
};
