#include <iostream>

#include "Excel/Excel.h"

int main()
{
	Excel excel;

	bool bSucceeded = true;
	while (true)
	{
		system("cls");

		excel.Print();

		if (!bSucceeded)
		{
			excel.HandleInvalidInput();
		}
		bSucceeded = excel.InputCommand();
	}

	return 0;
}
