#include "HelpCommand.h"

#include <cassert>

#include "Excel/Excel.h"

bool HelpCommand::Execute(Excel* excel, std::stringstream& ss)
{
	assert(excel);

	std::string subCmd;
	ss >> subCmd;

	if (subCmd.size() == 0)
	{
		excel->QueueMessages(helpStr);

		return true;
	}
	else
	{
		auto iter = SubCmds.find(subCmd);
		if (iter != SubCmds.end())
		{
			excel->QueueMessages(iter->second);

			return true;
		}
		else
		{
			excel->QueueMessage(NOT_FOUND_CMD);
		}
	}

	return false;
}
