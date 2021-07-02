#pragma once

#include <cassert>
#include <string>

class Cell;

class Table
{
public:
	Table() = delete;

	Table(int row, int col);

	Table(const Table& source);

	Table(Table&& source) noexcept;

	virtual ~Table();

	Table& operator=(const Table& source);

	Table& operator=(Table&& source) noexcept;

	void Set(Cell* cell, int row, int col);

	inline Cell* Get(int row, int col) const
	{
		assert(cells);
		assert(0 <= row && row < maxRow);
		assert(0 <= col && col < maxCol);

		return cells[row][col];
	}

	virtual std::string ToString() const;

private:
	void releaseMemory();

	inline std::string rowToString(int row) const
	{
		assert(0 <= row && row < ROW_LIMIT);

		return std::to_string(row + 1);
	}

	inline std::string colToString(int col) const
	{
		// TODO :: only works when 0 <= col <= 25 (A ~ Z) for now 
		assert(0 <= col && col < COL_LIMIT);

		return std::string(1, 'A' + col);
	}

	int getCellSize(int row, int col) const;

public:
	static const int ROW_LIMIT = 100;

	static const int COL_LIMIT = 26;

private:
	Cell*** cells;

	int maxRow;

	int maxCol;
};
