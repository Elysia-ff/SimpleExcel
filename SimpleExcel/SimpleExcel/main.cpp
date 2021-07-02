#include <iostream>

#include "Excel/Excel.h"

int main()
{
	Excel excel;

	while (true)
	{
		system("cls");

		excel.Print();
		excel.PrintQueuedMessage();

		if (excel.HasInputError())
		{
			excel.HandleInvalidInput();
		}
		excel.InputCommand();
	}

	return 0;
}
