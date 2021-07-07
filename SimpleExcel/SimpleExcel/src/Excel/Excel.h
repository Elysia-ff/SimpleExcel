#pragma once

#include <sstream>
#include <unordered_map>
#include <queue>

#include "Excel/Command/CreateCommand.h"
#include "Excel/Command/ResizeCommand.h"
#include "Excel/Command/DeleteCommand.h"
#include "Excel/Command/SetsCommand.h"
#include "Excel/Command/SetnCommand.h"
#include "Excel/Command/SetdCommand.h"
#include "Excel/Command/SeteCommand.h"
#include "Excel/Command/ImportCommand.h"
#include "Excel/Command/ExportCommand.h"
#include "Excel/Command/HelpCommand.h"

class Table;
class ICommand;

class Excel
{
	friend class CreateCommand;
	friend class ResizeCommand;
	friend class DeleteCommand;
	friend class SetsCommand;
	friend class SetnCommand;
	friend class SetdCommand;
	friend class SeteCommand;
	friend class ExportCommand;

public:
	Excel();

	Excel(const Excel& source);

	Excel(Excel&& source) noexcept;

	~Excel();

	Excel& operator=(const Excel& source);

	Excel& operator=(Excel && source) noexcept;

	void Print() const;

	void InputCommand();

	void HandleInvalidInput();

	inline bool HasInputError() const { return bHasInputError; }

	void QueueMessage(const std::string& msg);

	void PrintQueuedMessage();

private:
	Table* table;

	bool bHasInputError;

	std::queue<std::string> msgQueue;

	inline static std::unordered_map<std::string, ICommand*> Commands
	{
		{ "create", new CreateCommand() },
		{ "resize", new ResizeCommand() },
		{ "delete", new DeleteCommand() },
		{ "sets", new SetsCommand() },
		{ "setn", new SetnCommand() },
		{ "setd", new SetdCommand() },
		{ "sete", new SeteCommand() },

		{ "import", new ImportCommand() },
		{ "export", new ExportCommand() },

		{ "help", new HelpCommand() },
	};
};
