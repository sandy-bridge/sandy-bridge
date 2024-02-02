#pragma once
#include <iostream>
#include "Headers.h"

class DataStructure
{
private:
	HEADER_E* pStructure;
	static char GetSecondFirstLetter(ITEM7* pItem); //gets the first letter of the second word in ID
	static char* ValidateID(char* pInput);
	static std::string SerialiseItem(ITEM7* pItem);
public:
	DataStructure();
	~DataStructure();
	DataStructure(char* pFileName);
	friend std::ostream& operator<<(std::ostream& ostr, const DataStructure& str); //prints out
	void operator+=(ITEM7* pNewItem);
	int GetItemsNumber() const;
	ITEM7* GetItem(char* pId) const;
	DataStructure(const DataStructure &Original);
	void operator-=(char *pID);
	int operator==(DataStructure& Other);
	void Write(char* pFileName);
	DataStructure &operator=(const DataStructure &Right);
};

