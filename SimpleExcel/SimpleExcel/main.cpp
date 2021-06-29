#include <iostream>
#include <string>

#include "Table/Table.h"

#include "Table/Cell/StringCell.h"
#include "Table/Cell/NumberCell.h"

using namespace std;

int main()
{
	int row = 6;
	int col = 4;
	Table table(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int k = 0; k < col; k++)
		{
			table.Set(new NumberCell((i * col + k) * 10), i, k);
		}
	}

	cout << table.ToString() << endl;

	return 0;
}
