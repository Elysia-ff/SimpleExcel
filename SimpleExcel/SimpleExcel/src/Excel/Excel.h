#pragma once

#include <sstream>

class Table;

class Excel
{
public:
	Excel();

	Excel(const Excel& source);

	Excel(Excel&& source) noexcept;

	~Excel();

	Excel& operator=(const Excel& source);

	Excel& operator=(Excel && source) noexcept;

	void Print() const;

	bool InputCommand();

	void HandleInvalidInput();

private:
	bool isEmptyStream(std::stringstream& ss) const;

private:
	Table* table;

	bool bHasInputError;
};
