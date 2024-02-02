#include <iostream>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"
#include "DataStructure.h"

using namespace std;

int main()
{
	DataStructure *data = new DataStructure;
	for (int i=0; i<10;i++)
	{
		ITEM7* pItem = (ITEM7*)GetItem(7);
		*data += pItem;
	}
	cout << *data << endl;
	cout << "There are " << data->GetItemsNumber() << " items." << endl;
	ITEM7* pItemToFind = data->GetItem((char*)"Light Cyan");
	if (pItemToFind)
	{
		cout << "Found item with ID " << pItemToFind->pID << ", Code " << pItemToFind->Code << endl;
	}
	else
	{
		cout << "Item not found." << endl;
	}
	pItemToFind = data->GetItem((char*)"X X");
	if (pItemToFind)
	{
		cout << "Found item with ID " << pItemToFind->pID << ", Code " << pItemToFind->Code << endl;
	}
	else
	{
		cout << "Item not found." << endl;
	}
	DataStructure DS3, DS2 = *data;
	cout << DS2 << endl;
	*data -= (char*)"Banana Mania";
	
	*data -= (char*)"Persian Green";
	
	*data -= (char*)"Vegas Gold";
	cout << *data << endl;
	if(DS2 == *data)
	{
		cout << "Data structures are equal" << endl;
	}
	else
	{
		cout << "Data structures not equal" << endl;
	}
	data->Write((char*)"Data.bin");
	DS3 = *data;
	cout << DS3 << endl;
	DataStructure* FromFile = new DataStructure((char*)"Data.bin");
	delete data;
	cout << *FromFile << endl;
	return 0;
}