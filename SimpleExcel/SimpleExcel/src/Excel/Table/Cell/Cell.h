#pragma once

#include <string>

#include "StrongType/Int.h"

class Table;

class Cell
{
public:
	Cell() = delete;

	Cell(const Table* _table) : table(_table) {}

	Cell(const Cell& source) = default;

	Cell(Cell&& source) noexcept = default;

	virtual ~Cell() = default;

	Cell& operator=(const Cell& source) = default;

	Cell& operator=(Cell&& source) noexcept = default;

	virtual Cell* DeepCopy() const = 0;

	virtual std::string ToString() const = 0;

	virtual Int ToInt() const = 0;

protected:
	const Table* table;
};
