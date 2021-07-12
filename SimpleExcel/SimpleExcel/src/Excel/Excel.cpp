#include "Excel.h"

#include <iostream>
#include <sstream>

#include "Table/Table.h"

#include "Excel/Command/ICommand.h"

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

void Excel::InputCommand()
{
	assert(!bHasInputError && "Call HandleInvalidInput() first");

	std::cout << "> ";

	std::string input;
	std::getline(std::cin, input);

	std::stringstream stream(input);
	std::string command;
	
	stream >> command;
	auto iter = Commands.find(command);
	if (iter != Commands.end())
	{
		bHasInputError = !((*iter).second->Execute(this, stream));
	}
	else
	{
		bHasInputError = true;
	}
}

void Excel::HandleInvalidInput()
{
	std::cout << "Invalid input. see help [?command]" << std::endl;

	std::cin.clear();
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bHasInputError = false;
}

void Excel::QueueMessage(const std::string& msg)
{
	msgQueue.push(msg);
}

void Excel::QueueMessages(const std::vector<std::string>& msgs)
{
	for (const std::string& m : msgs)
	{
		msgQueue.push(m);
	}
}

void Excel::PrintQueuedMessage()
{
	while (msgQueue.size())
	{
		const std::string& msg = msgQueue.front();
		std::cout << msg << std::endl;

		msgQueue.pop();
	}
}
