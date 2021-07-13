#pragma once

#include <string>
#include <iostream>

#include "StrongType/Int.h"

class Table;

class Cell
{
	friend class Table;

public:
	enum class Type : unsigned char
	{
		String = 's',
		Number = 'n',
		Date = 'd',
		Expr = 'e',
	};

public:
	Cell() = delete;

	Cell(const Table* _table);

	Cell(const Cell& source) = default;

	Cell(Cell&& source) noexcept = default;

	virtual ~Cell() = default;

	Cell& operator=(const Cell& source) = default;

	Cell& operator=(Cell&& source) noexcept = default;

	virtual Cell* DeepCopy() const = 0;

	virtual std::string ToString() const = 0;

	virtual Int ToInt() const = 0;

	inline virtual Type GetType() const = 0;

	inline virtual std::string GetPlainText() const = 0;

protected:
	const Table* table;

	int tableRow;

	int tableCol;
};

std::istream& operator>>(std::istream& is, Cell::Type& cellType);
