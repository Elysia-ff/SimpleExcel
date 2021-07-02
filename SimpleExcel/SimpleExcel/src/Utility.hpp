#pragma once

#include <string>
#include <sstream>

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

	static bool IsAlpha(char c)
	{
		return 'A' <= c && c <= 'Z';
	}

	static bool IsNumber(char c)
	{
		return '0' <= c && c <= '9';
	}

	static bool IsNumber(const std::string& str, int idx = 0)
	{
		for (size_t i = idx; i < str.size(); i++)
		{
			if (!IsNumber(str[i]))
			{
				return false;
			}
		}

		return true;
	}

	static bool IsCell(const std::string& cell)
	{
		if (cell.size() < 2)
		{
			return false;
		}

		if (!IsAlpha(cell[0]))
		{
			return false;
		}

		return IsNumber(cell, 1);
	}

	static void ParseRowCol(const std::string& cell, int* outRow, int* outCol)
	{
		assert(outRow);
		assert(outCol);
		assert(cell.size() >= 2);

		// TODO :: only works when 0 <= col <= 25 (A ~ Z) for now 
		*outCol = cell[0] - 'A';
		*outRow = atoi(cell.c_str() + 1) - 1;
	}

	static bool IsValidStream(std::stringstream& ss)
	{
		if (ss.fail())
		{
			return false;
		}

		std::string rest;
		ss >> rest;

		return rest.size() == 0;
	}
};
