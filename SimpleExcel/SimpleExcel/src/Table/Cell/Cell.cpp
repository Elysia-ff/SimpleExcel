#include "Cell.h"

Cell::Cell(const std::string& _data)
	: data(_data)
{
}

Cell::Cell(std::string&& _data)
	: data(std::move(_data))
{
}
