#pragma once

#include <vector>
#include <unordered_map>

#include "Cell.h"

class ExprCell : public Cell
{
public:
	ExprCell() = delete;

	ExprCell(const Table* _table, const std::string& _expr);

	ExprCell(const ExprCell& source) = default;

	ExprCell(ExprCell&& source) noexcept = default;

	virtual ~ExprCell() = default;

	ExprCell& operator=(const ExprCell& source) = default;

	ExprCell& operator=(ExprCell&& source) noexcept = default;

	virtual Cell* DeepCopy() const override;

	virtual std::string ToString() const override;

	virtual Int ToInt() const override;

	inline virtual Type GetType() const override { return Type::Expr; }

	inline virtual std::string GetPlainText() const override { return expr; }

private:
	// remove white characters, capitalize, replace '{', '[' to '(' 
	std::string normalize(const std::string& str) const;

	std::vector<std::string> split(const std::string& str) const;

	std::vector<std::string> toPostfix(const std::vector<std::string>& infix) const;

private:
	std::string expr;

	inline static std::unordered_map<EErrorCode, std::string> ErrorStr
	{
		{ EErrorCode::N_A, "!N/A" },
		{ EErrorCode::DIV_ZERO, "!DIV/0" },
		{ EErrorCode::CIRCULAR_REF, "!CIRCULAR_REF" },
	};

	inline static std::unordered_map<char, int> OperatorPriorities
	{
		{ '(', 1 },
		{ ')', 1 },

		{ '+', 2 },
		{ '-', 2 },

		{ '*', 3 },
		{ '/', 3 }
	};
};
