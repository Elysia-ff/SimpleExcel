#pragma once

#include "Excel/Command/ICommand.h"

class SetnCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;
};
