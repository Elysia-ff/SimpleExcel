#pragma once

#include "Excel/Command/ICommand.h"

class SetdCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;
};
