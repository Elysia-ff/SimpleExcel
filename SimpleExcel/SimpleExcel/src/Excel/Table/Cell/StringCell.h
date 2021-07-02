#pragma once

#include "Cell.h"

class StringCell : public Cell
{
public:
	StringCell() = delete;

	StringCell(const Table* _table, const std::string& _str);

	StringCell(const Table* _table, std::string&& _str);

	StringCell(const StringCell& source) = default;

	StringCell(StringCell&& source) noexcept = default;

	virtual ~StringCell() = default;

	StringCell& operator=(const StringCell& source) = default;

	StringCell& operator=(StringCell&& source) noexcept = default;

	virtual Cell* DeepCopy() const override;

	virtual std::string ToString() const override;

	virtual Int ToInt() const override;

private:
	std::string str;
};
