#pragma once

#include "Cell.h"

class NumberCell : public Cell
{
public:
	NumberCell() = delete;

	NumberCell(const Table* _table, int _num);

	NumberCell(const NumberCell& source) = default;

	NumberCell(NumberCell&& source) noexcept = default;

	virtual ~NumberCell() = default;

	NumberCell& operator=(const NumberCell& source) = default;

	NumberCell& operator=(NumberCell&& source) noexcept = default;

	virtual Cell* DeepCopy() const override;

	virtual std::string ToString() const override;

	virtual Int ToInt() const override;

	inline virtual Type GetType() const override { return Type::Number; }

	inline virtual std::string GetPlainText() const override { return ToString(); }

private:
	int num;
};
