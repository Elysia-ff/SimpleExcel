#pragma once

#include "Cell.h"

class DateCell : public Cell
{
public:
	DateCell() = delete;

	DateCell(const std::string& _data);

	DateCell(std::string&& _data);

	DateCell(const DateCell& source) = default;

	DateCell(DateCell&& source) noexcept = default;

	virtual ~DateCell() = default;

	DateCell& operator=(const DateCell& source) = default;

	DateCell& operator=(DateCell&& source) noexcept = default;

	virtual Cell* DeepCopy() const override;

	virtual int ToInt() const override;
};
