#pragma once

#include "Excel/Command/ICommand.h"

class DeleteCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;
};
