#include <iostream>
#include <string>

#include "Table/Table.h"

#include "Table/Cell/StringCell.h"

using namespace std;

int main()
{
	int row = 6;
	int col = 4;
	Table table(row, col);
	for (int i = 0; i < row; i++)
	{
		std::string input(static_cast<size_t>(i) + 1, 'a' + i);
		for (int k = 0; k < col; k++)
		{
			table.Set(new StringCell(input), i, k);
		}
	}

	cout << table.ToString() << endl;

	return 0;
}
