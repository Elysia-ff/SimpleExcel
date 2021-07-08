#pragma once

#include "Cell.h"

class DateCell : public Cell
{
public:
	DateCell() = delete;

	DateCell(const Table* _table, const std::string& data);

	DateCell(const DateCell& source) = default;

	DateCell(DateCell&& source) noexcept = default;

	virtual ~DateCell() = default;

	DateCell& operator=(const DateCell& source) = default;

	DateCell& operator=(DateCell&& source) noexcept = default;

	virtual Cell* DeepCopy() const override;

	virtual std::string ToString() const override;

	virtual Int ToInt() const override;
	
	inline virtual Type GetType() const override { return Type::Date; }

	inline virtual std::string GetPlainText() const override { return ToString(); }

private:
	void parse(const std::string& str);

private:
	int year;

	int month;

	int day;
};
