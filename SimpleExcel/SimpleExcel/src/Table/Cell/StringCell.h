#pragma once

#include "Cell.h"

class StringCell : public Cell
{
public:
	StringCell() = delete;

	StringCell(const std::string& _data);

	StringCell(std::string&& _data);

	StringCell(const StringCell& source) = default;

	StringCell(StringCell&& source) noexcept = default;

	virtual ~StringCell() = default;

	StringCell& operator=(const StringCell& source) = default;

	StringCell& operator=(StringCell&& source) noexcept = default;

	virtual Cell* DeepCopy() const override;

	virtual int ToInt() const override;
};
