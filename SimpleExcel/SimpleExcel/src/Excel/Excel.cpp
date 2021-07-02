#include "Excel.h"

#include <iostream>
#include <sstream>

#include "Table/Table.h"

Excel::Excel()
	: table(nullptr)
	, bHasInputError(false)
{
}

Excel::Excel(const Excel& source)
	: table(nullptr)
	, bHasInputError(source.bHasInputError)
{
	if (source.table != nullptr)
	{
		table = new Table(*(source.table));
	}
}

Excel::Excel(Excel&& source) noexcept
	: table(source.table)
	, bHasInputError(source.bHasInputError)
{
	source.table = nullptr;
	source.bHasInputError = false;
}

Excel::~Excel()
{
	if (table)
	{
		delete table;
	}
}

Excel& Excel::operator=(const Excel& source)
{
	if (this != &source && source.table)
	{
		table = new Table(*(source.table));
		bHasInputError = source.bHasInputError;
	}

	return *this;
}

Excel& Excel::operator=(Excel&& source) noexcept
{
	if (this != &source)
	{
		if (table)
		{
			delete table;
		}

		table = source.table;
		bHasInputError = source.bHasInputError;

		source.table = nullptr;
		source.bHasInputError = false;
	}

	return *this;
}

void Excel::Print() const
{
	if (table)
	{
		std::cout << table->ToString() << std::endl;
	}
}

bool Excel::InputCommand()
{
	assert(!bHasInputError && "Call HandleInvalidInput() first");

	std::cout << "> ";

	std::string input;
	std::getline(std::cin, input);

	std::stringstream stream(input);
	std::string command;
	
	stream >> command;
	if (command == "create")
	{
		int row;
		int col;
		stream >> row >> col;

		if (!stream.fail() && isEmptyStream(stream) &&
			0 < row && row <= Table::ROW_LIMIT &&
			0 < col && col <= Table::COL_LIMIT)
		{
			if (table)
			{
				delete table;
			}
			
			table = new Table(row, col);
		}
		else
		{
			bHasInputError = true;
			return false;
		}
	}
	else
	{
		bHasInputError = true;
		return false;
	}

	return true;
}

void Excel::HandleInvalidInput()
{
	std::cout << "Invalid input. see help [?command]" << std::endl;

	std::cin.clear();
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bHasInputError = false;
}

bool Excel::isEmptyStream(std::stringstream& ss) const
{
	std::string rest;
	ss >> rest;

	return rest.size() == 0;
}
