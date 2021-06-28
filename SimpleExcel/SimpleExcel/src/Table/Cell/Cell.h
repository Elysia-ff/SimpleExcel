#pragma once

#include <string>

class Cell
{
public:
	Cell() = default;

	Cell(const std::string& _data);

	Cell(std::string&& _data);

	Cell(const Cell& source) = default;

	Cell(Cell&& source) noexcept = default;

	virtual ~Cell() = default;

	Cell& operator=(const Cell& source) = default;

	Cell& operator=(Cell&& source) noexcept = default;

	virtual Cell* DeepCopy() const = 0;

	inline const std::string& ToString() const
	{
		return data;
	}

	virtual int ToInt() const = 0;

private:
	std::string data;
};
