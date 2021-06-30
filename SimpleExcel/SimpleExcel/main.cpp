#include <iostream>
#include <string>

#include "Table/Table.h"

#include "Table/Cell/StringCell.h"
#include "Table/Cell/NumberCell.h"
#include "Table/Cell/DateCell.h"
#include "Table/Cell/ExprCell.h"

using namespace std;

int main()
{
	int row = 1;
	int col = 5;
	Table table(row, col);

	table.Set(new NumberCell(&table, 10), 0, 0);
	table.Set(new NumberCell(&table, 11), 0, 1);
	table.Set(new NumberCell(&table, 12), 0, 2);
	table.Set(new ExprCell(&table, "(A1 + B1 + C1) * 100 / 2 - 10"), 0, 3);
	table.Set(new ExprCell(&table, "3 / 0"), 0, 4);

	cout << table.ToString();

	return 0;
}
