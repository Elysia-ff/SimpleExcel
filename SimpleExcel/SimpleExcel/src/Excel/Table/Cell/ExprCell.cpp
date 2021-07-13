#include "ExprCell.h"

#include <cassert>
#include <stack>

#include "Excel/Table/Table.h"
#include "Utility.hpp"

ExprCell::ExprCell(const Table* _table, const std::string& _expr)
	: Cell(_table)
	, expr(_expr)
{
}

Cell* ExprCell::DeepCopy() const
{
	return new ExprCell(*this);
}

std::string ExprCell::ToString() const
{
	Int value = ToInt();

	if (value.error != EErrorCode::NONE)
	{
		assert(ErrorStr.find(value.error) != ErrorStr.end());

		return ErrorStr[value.error];
	}

	return std::to_string(value.v);
}

Int ExprCell::ToInt() const
{
	std::string data = normalize(expr);
	std::vector<std::string> infix = split(data);
	std::vector<std::string> postfix = toPostfix(infix);

	std::stack<int> stack;
	for (int i = 0; i < postfix.size(); i++)
	{
		const std::string& str = postfix[i];

		if (Utility::IsCell(str))
		{
			assert(table);

			int row;
			int col;
			Utility::ParseRowCol(str, &row, &col);

			if (row == tableRow && col && tableCol)
			{
				return Int{ 0, EErrorCode::CIRCULAR_REF };
			}

			if (!(0 <= row && row < table->GetMaxRow() &&
				0 <= col && col < table->GetMaxCol()))
			{
				return Int{ 0, EErrorCode::N_A };
			}

			Cell* cell = table->Get(row, col);
			if (cell != nullptr)
			{
				Int value = cell->ToInt();
				if (value.error != EErrorCode::NONE)
				{
					return value;
				}

				stack.push(value.v);
			}
			else
			{
				stack.push(0);
			}
		}
		else if (Utility::IsNumber(str))
		{
			int value = atoi(str.c_str());
			stack.push(value);
		}
		else if (OperatorPriorities.find(str[0]) != OperatorPriorities.end())
		{
			if (stack.size() < 2)
			{
				return Int{ 0, EErrorCode::N_A };
			}

			int v2 = stack.top();
			stack.pop();

			int v1 = stack.top();
			stack.pop();

			switch (str[0])
			{
			case '*':
				stack.push(v1 * v2);
				break;

			case '/':
				if (v2 == 0)
				{
					return Int{ 0, EErrorCode::DIV_ZERO };
				}

				stack.push(v1 / v2);
				break;

			case '+':
				stack.push(v1 + v2);
				break;

			case '-':
				stack.push(v1 - v2);
				break;

			default:
				assert(false);
			}
		}
		else
		{
			return Int{ 0, EErrorCode::N_A };
		}
	}

	return stack.size() == 1 ? Int{ stack.top(), EErrorCode::NONE } : Int{ 0, EErrorCode::N_A };
}

std::string ExprCell::normalize(const std::string& str) const
{
	std::string result;
	result.reserve(str.size());

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			continue;
		}

		char c = str[i];
		if ('a' <= str[i] && str[i] <= 'z')
		{
			c = str[i] - 32;
		}
		else if (str[i] == '{' || str[i] == '[')
		{
			c = '(';
		}
		else if (str[i] == '}' || str[i] == ']')
		{
			c = ')';
		}

		result.append(1, c);
	}

	return result;
}

std::vector<std::string> ExprCell::split(const std::string& str) const
{
	std::vector<std::string> result;

	auto iter = str.begin();
	auto index = str.begin();
	for (; iter != str.end(); ++iter)
	{
		if (*iter == '+' || *iter == '-' || *iter == '*' || *iter == '/' ||
			*iter == '(' || *iter == ')')
		{
			if (iter - index > 0)
			{
				result.emplace_back(index, iter);
			}
			result.emplace_back(1, *iter);

			index = iter;
			++index;
		}
	}

	if (str.end() - index > 0)
	{
		result.emplace_back(index, str.end());
	}

	return result;
}

std::vector<std::string> ExprCell::toPostfix(const std::vector<std::string>& infix) const
{
	std::vector<std::string> result;

	std::stack<char> stack;
	for (size_t i = 0; i < infix.size(); i++)
	{
		const std::string& str = infix[i];

		auto opIter = OperatorPriorities.find(str[0]);
		if (opIter != OperatorPriorities.end())
		{
			if (str[0] == '(')
			{
				stack.push(str[0]);
			}
			else if (str[0] == ')')
			{
				while (stack.size())
				{
					if (stack.top() == '(')
					{
						stack.pop();
						break;
					}

					result.emplace_back(1, stack.top());
					stack.pop();
				}
			}
			else
			{
				const auto& opPair = *opIter;
				while (stack.size() && OperatorPriorities[stack.top()] >= opPair.second)
				{
					result.emplace_back(1, stack.top());
					stack.pop();
				}

				stack.push(opPair.first);
			}
		}
		else
		{
			result.push_back(str);
		}
	}

	while (stack.size())
	{
		result.emplace_back(1, stack.top());
		stack.pop();
	}

	return result;
}
