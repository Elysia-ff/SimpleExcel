#pragma once

#include "Excel/Command/ICommand.h"

class ImportCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;
};
