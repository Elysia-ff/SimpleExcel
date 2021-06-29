#pragma once

#include "Cell.h"

class NumberCell : public Cell
{
public:
	NumberCell() = delete;

	NumberCell(int _data);

	NumberCell(const NumberCell& source) = default;

	NumberCell(NumberCell&& source) noexcept = default;

	virtual ~NumberCell() = default;

	NumberCell& operator=(const NumberCell& source) = default;

	NumberCell& operator=(NumberCell&& source) noexcept = default;

	virtual Cell* DeepCopy() const override;

	virtual int ToInt() const;
};
