#pragma once

#include <vector>
#include <unordered_map>

#include "Excel/Table/Table.h"
#include "Excel/Command/ICommand.h"

class HelpCommand : public ICommand
{
public:
	virtual bool Execute(Excel* excel, std::stringstream& ss) override;

private:
	inline static const std::vector<std::string> helpStr =
	{
		{ "commands" },
		{ "    create [row] [col]" },
		{ "    resize [row] [col]" },
		{ "    delete [cell]" },
		{ "    sets [cell] [str]" },
		{ "    setn [cell] [int]" },
		{ "    setd [cell] [date]" },
		{ "    sete [cell] [expression]" },
		{ "    import [path]" },
		{ "    export [path]" },
	};

	inline static const std::unordered_map<std::string, std::vector<std::string>> SubCmds =
	{
		{ "create",
			{
			{ "create [row] [col]" },
			{ "0 < [row] <= " + std::to_string(Table::ROW_LIMIT) },
			{ "0 < [col] <= " + std::to_string(Table::COL_LIMIT) },
			{ "existing table will be deleted" },
			{ "ex) create 2 5" },
			}
		},

		{ "resize",
			{
			{ "resize [row] [col]" },
			{ "0 < [row] <= " + std::to_string(Table::ROW_LIMIT) },
			{ "0 < [col] <= " + std::to_string(Table::COL_LIMIT) },
			{ "exising table will be copy-pasted to new one" },
			{ "ex) resize 5 2" },
			}
		},

		{ "delete",
			{
			{ "delete [cell]" },
			{ "if [cell] == \"all\", entire table will be deleted" },
			{ "ex) delete all" },
			{ "    delete A1" },
			}
		},

		{ "sets",
			{
			{ "sets [cell] [str]" },
			{ "ex) sets A1 an example text" },
			}
		},

		{ "setn",
			{
			{ "setn [cell] [int]" },
			{ "ex) setn A1 123" },
			}
		},

		{ "setd",
			{
			{ "setd [cell] [date]" },
			{ "[date] should be YYYY-MM-DD form" },
			{ "ex) setd A1 1990-01-01" },
			}
		},

		{ "sete",
			{
			{ "sete [cell] [expression]" },
			{ "ex) sete D1 (A1 + B1 + C1) / 3" },
			}
		},

		{ "import",
			{
			{ "import [path]" },
			{ "extension - .se" },
			{ "ex) import output.se" },
			}
		},

		{ "export",
			{
			{ "export [path]" },
			{ "extension - .csv, .se" },
			{ "ex) export output.se" },
			}
		}
	};

	inline static const std::string NOT_FOUND_CMD = "Not found command";
};
