#pragma once

#include <sstream>

class Excel;

class ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) = 0;
};
