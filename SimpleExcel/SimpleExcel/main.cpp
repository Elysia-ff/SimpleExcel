#include <iostream>
#include <string>

#include "Table/Table.h"

#include "Table/Cell/StringCell.h"
#include "Table/Cell/NumberCell.h"
#include "Table/Cell/DateCell.h"

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
			DateCell* cell = new DateCell("1970-01-02");
			table.Set(cell, i, k);
		}
	}

	cout << table.ToString() << endl;

	return 0;
}
