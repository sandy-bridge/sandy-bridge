#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "DataStructure.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

DataStructure::DataStructure()
{
	pStructure = nullptr;
}
DataStructure::~DataStructure()
{
	for (HEADER_E* p = pStructure; p; p = p->pNext)
	{
		ITEM7** ppItems;
		int i;
		for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++)
		{
			for (ITEM7* pItem = (ITEM7*)*(ppItems + i); pItem; )
			{
				ITEM7* tmp = pItem; //frees linked list nodes
				pItem = pItem->pNext;
				free(tmp->pDate);
				free(tmp->pID);
				free(tmp);
			}
		}
		free(ppItems);
	}
	free(pStructure);
}
DataStructure::DataStructure(char* pFileName)
{
	fstream File;
	File.open(pFileName, fstream::in | fstream::binary);
	do
	{
		ITEM7* pNewItem = new ITEM7;
		char buf[80];
		int spaceCount = 0;
		if(File.peek() == '\n')
		{
			File.seekg(1, ios_base::cur);
		}
		else {
			break;
		}
		for (int i = 0; i<80; i++)
		{
			if(File.peek() == ' ' && spaceCount == 1)
			{
				File.seekg(1, ios_base::cur);
				buf[i] = '\0';
				break;
			}
			else if(File.peek() == ' ')
			{
				buf[i] = File.get();
				spaceCount++;
			}
			else
			{
				buf[i] = File.get();
			}
		}
		pNewItem->pID = new char [strlen(buf) + 1];
		strcpy_s(pNewItem->pID, strlen(buf) +1, buf);
		for (int i = 0; i<30; i++)
		{
			if(File.peek() == ' ')
			{
				File.seekg(1, ios_base::cur);
				buf[i] = '\0';
				break;
			}
			else
			{
				buf[i] = File.get();
			}
		}
		pNewItem->Code = atol(buf);
		pNewItem->pDate = new DATE2;
		for (int i = 0; i<30; i++)
		{
			if(File.peek() == ' ')
			{
				File.seekg(1, ios_base::cur);
				buf[i] = '\0';
				break;
			}
			else
			{
				buf[i] = File.get();
			}
		}
		pNewItem->pDate->Day = atoi(buf);
		for (int i = 0; i<4; i++)
		{
			buf[i] = File.get();
		}
		buf[3] = '\0';
		strcpy_s(pNewItem->pDate->Month, 4, buf);
		for (int i = 0; i<30; i++)
		{
			if(File.peek() == '\n')
			{
				buf[i] = '\0';
				break;
			}
			else
			{
				buf[i] = File.get();
			}
		}
		pNewItem->pDate->Year = atoi(buf);
		pNewItem->pNext = nullptr;
		*this += pNewItem;
	} while(File.peek() == '\n');
}
char DataStructure::GetSecondFirstLetter(ITEM7* pItem)
{
	char* pID = pItem->pID;
	for (; *pID != ' '; pID++);
	return *(pID + 1);
}
char* DataStructure::ValidateID(char* pInput)
{
	if (strlen(pInput) < 3) //checks minimum length
	{
		printf("Input too short!");
		return 0;
	}
	int spaces = 0;
	for (int i = 0; i < strlen(pInput); i++)
	{
		if (*(pInput + i) == ' ')
		{
			spaces++;
		}
	}
	if (spaces != 1)
	{
		printf("Space error\n");
		return 0;
	}
	if (*pInput > 90 || *pInput < 65)
	{
		printf("First letter not capital\n");
		return 0;
	}
	const char* pSpace = pInput;
	for (; *pSpace != ' '; pSpace++);
	if (*(pSpace + 1) > 90 || *(pSpace + 1) < 65)
	{
		printf("First letter of second word not capital\n");
		return 0;
	}
	return pInput;
}
string DataStructure::SerialiseItem(ITEM7* pItem)
{
	stringstream sout;
	sout << pItem->pID << " " << pItem->Code << " " << pItem->pDate->Day << " " << pItem->pDate->Month << " " << pItem->pDate->Year << endl;
	return sout.str();
}
std::ostream& operator<<(std::ostream& ostr, const DataStructure& str)
{
	int itemCount = 1;
	for (HEADER_E* p = str.pStructure; p; p = p->pNext) //iterates through linked list.
	{
		ITEM7** ppItems;
		int i;
		for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++) //iterate through array of pointers, all letters of the alphabet
		{
			for (ITEM7* pItem = *(ppItems + i); pItem; pItem = pItem->pNext, itemCount++) //dereference pointer and iterate through linked list
			{
				ostr << itemCount << ") " << pItem->pID << ' ' << pItem->Code << ' ' << pItem->pDate->Day << ' ' << pItem->pDate->Month << ' ' << pItem->pDate->Year << endl;
			}
		}
	}
	return ostr;
}
void DataStructure::operator+=(ITEM7* pNewItem)
{
	char letter = *(pNewItem->pID); //get first letter
	if (!pStructure)
	{
		pStructure = new HEADER_E;
		pStructure->cBegin = letter;
		pStructure->ppItems = (void**)calloc(26, sizeof(ITEM7*));
		pStructure->pPrior = nullptr;
		pStructure->pNext = nullptr;
	}
	HEADER_E* p = pStructure;
	while(p)
	{
		if(p->cBegin == letter) //header exists
		{
			break;
		}
		else if (p->cBegin > letter) //finds correct place to insert
		{
			if(p->pPrior)
			{
				p = p->pPrior;
			}
			break;
		}
		else if (p->pNext)
		{
			p = p->pNext;
			continue;
		}
		break;
	}
	if(p->cBegin != letter)
	{
		HEADER_E *pNew = new HEADER_E;
		pNew->cBegin = letter;
		pNew->ppItems = (void**)calloc(26, sizeof(ITEM7*));
		if(p->cBegin < letter)
		{
			pNew->pPrior = p;
			pNew->pNext = p->pNext;
			if(pNew->pNext)
			{
				pNew->pNext->pPrior = pNew;
			}
			p->pNext = pNew;
			p = pNew;
		}
		else //first header
		{
			p->pPrior = pNew;
			pNew->pPrior = nullptr;
			pNew->pNext = p;
			p = pNew;
		}
	}
	letter = GetSecondFirstLetter(pNewItem);
	if(*((p->ppItems)+letter-65) != 0)
	{
		pNewItem->pNext = (ITEM7*)*(p->ppItems + letter - 65);
	}
	*(p->ppItems + letter - 65) = pNewItem;
	while(this->pStructure->pPrior)
	{
		this->pStructure = pStructure->pPrior;
	}
}

int DataStructure::GetItemsNumber() const
{
	int itemCount=1;
	for(HEADER_E* p = this->pStructure; p; p=p->pNext)
	{
		itemCount++;
	}
	if (pStructure->pNext)
	{
		itemCount++;
	}
	return itemCount;
}

ITEM7* DataStructure::GetItem(char* pId) const
{
	for (HEADER_E* p = this->pStructure; p; p = p->pNext)
	{
		ITEM7** ppItems;
		int i;
		for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++)
		{
			for (ITEM7* pItem = *(ppItems + i); pItem; pItem = pItem->pNext) 
			{
				if(!strcmp(pItem->pID, pId))
				{
					return pItem;
				}
			}
		}
	}
	return nullptr;
}

DataStructure::DataStructure(const DataStructure& Original)
{
	this->pStructure = new HEADER_E;
	this->pStructure->cBegin = Original.pStructure->cBegin;
	this->pStructure->ppItems = (void**)calloc(26, sizeof(ITEM7*));
	ITEM7** ppItems;
	int i;
	for (ppItems = (ITEM7**)Original.pStructure->ppItems, i = 0; i < 26; i++)
	{
		if(*(ppItems+i))
		{
			*((this->pStructure->ppItems)+i) = new ITEM7;
			for(ITEM7* pItem = *(ppItems+i), *pNewItem = (ITEM7*)*((this->pStructure->ppItems)+i); pItem; pItem = pItem->pNext, pNewItem = pNewItem->pNext)
			{
				pNewItem->pID = new char[strlen(pItem->pID) + 1];
				strcpy_s(pNewItem->pID, strlen(pItem->pID)+1, pItem->pID);
				pNewItem->Code = pItem->Code;
				pNewItem->pDate = new DATE2;
				pNewItem->pDate->Day = pItem->pDate->Day;
				pNewItem->pDate->Year = pItem->pDate->Year;
				strcpy_s(pNewItem->pDate->Month, 4, pItem->pDate->Month);
				if(pItem->pNext)
				{
					pNewItem->pNext = new ITEM7;
				}
				else
				{
					pNewItem->pNext = nullptr;
				}
			}
		}
	}
	this->pStructure->pPrior = nullptr;
	for (HEADER_E* p = Original.pStructure->pNext, *pNew = this->pStructure; p; p = p->pNext)
	{
		pNew->pNext = new HEADER_E;
		pNew->pNext->pPrior = pNew;
		pNew = pNew->pNext;
		pNew->cBegin = p->cBegin;
		pNew->ppItems = (void**)calloc(26, sizeof(ITEM7*));
		if(!p->pNext)
		{
			pNew->pNext = nullptr;
		}
		for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++)
		{
			if(*(ppItems+i))
			{
				*((pNew->ppItems)+i) = new ITEM7;
				for(ITEM7* pItem = *(ppItems+i), *pNewItem = (ITEM7*)*((pNew->ppItems)+i); pItem; pItem = pItem->pNext, pNewItem = pNewItem->pNext)
				{
					pNewItem->pID = new char[strlen(pItem->pID) + 1];
					strcpy_s(pNewItem->pID, strlen(pItem->pID)+1, pItem->pID);
					pNewItem->Code = pItem->Code;
					pNewItem->pDate = new DATE2;
					pNewItem->pDate->Day = pItem->pDate->Day;
					pNewItem->pDate->Year = pItem->pDate->Year;
					strcpy_s(pNewItem->pDate->Month, 4, pItem->pDate->Month);
					if(pItem->pNext)
					{
						pNewItem->pNext = new ITEM7;
					}
					else
					{
						pNewItem->pNext = nullptr;
					}
				}
			}
		}
	}
}

void DataStructure::operator-=(char* pID)
{
	pID = ValidateID(pID);
	if (pID == 0 || pID == "")
	{
		printf("Item ID not provided or input rules not followed!\n");
		return;
	}
	ITEM7* pItem = 0;
	ITEM7** ppItems = 0;
	HEADER_E* pHeaderToRemove = pStructure;
	int i = 0;
	bool found = false;
	while (pHeaderToRemove && found == false) //finds item to remove
	{
		for (ppItems = (ITEM7**)pHeaderToRemove->ppItems, i = 0; i < 26 && found == false;)
		{
			for (pItem = (ITEM7*)*(ppItems+i); pItem; pItem=pItem->pNext)
			{
				if(!strcmp(pID, (pItem->pID)))
				{
					found = true; //breaks both loops
					break;
				}
			}
			if (found == false)
			{
				i++;
			}
		}
		if (found == false) //only move forward if header is not yet found
		{
			pHeaderToRemove = pHeaderToRemove->pNext;
		}
	} //pItem now points to item to be removed
	if(*(ppItems+i) == pItem)
	{
		*(ppItems + i) = pItem->pNext;
		free(pItem->pDate);
		free(pItem);
	}
	else
	{
		ITEM7* pPrior;
		for(pPrior = *(ppItems+i); pPrior; pPrior=pPrior->pNext)
		{
			if (pPrior->pNext == pItem)
			{
				break;
			}
		}
		pPrior->pNext = pItem->pNext;
		free(pItem);
	}
	int zeroCount = 0;
	for(i = 0; i < 26; i++) //checks if header is empty
	{
		if(!(*(ppItems+i)))
		{
			zeroCount++;
		}
	}
	if(zeroCount == 26) //frees header if empty
	{
		free(ppItems);
		if (pHeaderToRemove->pPrior) 
		{
			pHeaderToRemove->pPrior->pNext = pHeaderToRemove->pNext;
		}
		if (pHeaderToRemove->pNext)
		{
			if (!pHeaderToRemove->pPrior)
			{
				pStructure = pStructure->pNext;
			}
			pHeaderToRemove->pNext->pPrior = pHeaderToRemove->pPrior;
		}
		free(pHeaderToRemove);
	}
}

int DataStructure::operator==(DataStructure& Other)
{
	HEADER_E* p = this->pStructure;
	HEADER_E* pOther = Other.pStructure;
	int equals = 1;
	for(; p && pOther && equals; p=p->pNext, pOther=pOther->pNext)
	{
		if(p->cBegin != pOther->cBegin)
		{
			equals = 0;
			break;
		}
		ITEM7** ppItems = (ITEM7**)p->ppItems;
		ITEM7** ppOtherItems = (ITEM7**)pOther->ppItems;
		for(int i = 0; i<26 && equals; i++)
		{
			if((*(ppItems+i) && !*(ppOtherItems+i)) || ((!*(ppItems+i)) && (*(ppOtherItems+i))))
			{
				equals = 0;
				break;
			}
			ITEM7* pItem = *(ppItems + i);
			ITEM7* pOtherItem = *(ppOtherItems + i);
			for(; pItem && pOtherItem && equals; pItem=pItem->pNext, pOtherItem=pOtherItem->pNext)
			{
				if(strcmp(pItem->pID, pOtherItem->pID))
				{
					equals = 0;
					break;
				}
				else if(pItem->Code != pOtherItem->Code)
				{
					equals = 0;
					break;
				}
				else if(pItem->pDate->Day != pOtherItem->pDate->Day)
				{
					equals = 0;
					break;
				}
				else if(strcmp(pItem->pDate->Month, pOtherItem->pDate->Month))
				{
					equals = 0;
					break;
				}
				else if(pItem->pDate->Year != pOtherItem->pDate->Year)
				{
					equals = 0;
					break;
				}
			}
		}
	}
	return equals;
}

void DataStructure::Write(char* pFileName)
{
	if(!this->pStructure)
	{
		cout << "Empty structure" << endl;
		return;
	}
	stringstream sout;
	for (HEADER_E* p = this->pStructure; p; p=p->pNext)
	{
		for(int i = 0; i<26; i++)
		{
			for(ITEM7* pItem = (ITEM7*)*(p->ppItems+i); pItem; pItem=pItem->pNext)
			{
				sout << SerialiseItem(pItem);
			}
		}
	}
	fstream File;
	File.open(pFileName, fstream::out | fstream::binary);
	File.write(sout.str().c_str(), strlen(sout.str().c_str()));
	if(!File.good())
	{
		cout << "Failed to write!" << endl;
	}
	File.close();
}

DataStructure& DataStructure::operator=(const DataStructure& Right)
{
	if(this == &Right)
	{
		return *this;
	}
	for (HEADER_E* p = this->pStructure; p; p = p->pNext)
	{
		ITEM7** ppItems;
		int i;
		for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++)
		{
			for (ITEM7* pItem = (ITEM7*)*(ppItems + i); pItem; )
			{
				ITEM7* tmp = pItem; //frees linked list nodes
				pItem = pItem->pNext;
				free(tmp->pDate);
				free(tmp->pID);
				free(tmp);
			}
		}
		free(ppItems);
	}
	free(this->pStructure);
	this->pStructure = new HEADER_E;
	this->pStructure->cBegin = Right.pStructure->cBegin;
	this->pStructure->ppItems = (void**)calloc(26, sizeof(ITEM7*));
	ITEM7** ppItems;
	int i;
	for (ppItems = (ITEM7**)Right.pStructure->ppItems, i = 0; i < 26; i++)
	{
		if(*(ppItems+i))
		{
			*((this->pStructure->ppItems)+i) = new ITEM7;
			for(ITEM7* pItem = *(ppItems+i), *pNewItem = (ITEM7*)*((this->pStructure->ppItems)+i); pItem; pItem = pItem->pNext, pNewItem = pNewItem->pNext)
			{
				pNewItem->pID = new char[strlen(pItem->pID) + 1];
				strcpy_s(pNewItem->pID, strlen(pItem->pID)+1, pItem->pID);
				pNewItem->Code = pItem->Code;
				pNewItem->pDate = new DATE2;
				pNewItem->pDate->Day = pItem->pDate->Day;
				pNewItem->pDate->Year = pItem->pDate->Year;
				strcpy_s(pNewItem->pDate->Month, 4, pItem->pDate->Month);
				if(pItem->pNext)
				{
					pNewItem->pNext = new ITEM7;
				}
				else
				{
					pNewItem->pNext = nullptr;
				}
			}
		}
	}
	this->pStructure->pPrior = nullptr;
	for (HEADER_E* p = Right.pStructure->pNext, *pNew = this->pStructure; p; p = p->pNext)
	{
		pNew->pNext = new HEADER_E;
		pNew->pNext->pPrior = pNew;
		pNew = pNew->pNext;
		pNew->cBegin = p->cBegin;
		pNew->ppItems = (void**)calloc(26, sizeof(ITEM7*));
		if(!p->pNext)
		{
			pNew->pNext = nullptr;
		}
		for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++)
		{
			if(*(ppItems+i))
			{
				*((pNew->ppItems)+i) = new ITEM7;
				for(ITEM7* pItem = *(ppItems+i), *pNewItem = (ITEM7*)*((pNew->ppItems)+i); pItem; pItem = pItem->pNext, pNewItem = pNewItem->pNext)
				{
					pNewItem->pID = new char[strlen(pItem->pID) + 1];
					strcpy_s(pNewItem->pID, strlen(pItem->pID)+1, pItem->pID);
					pNewItem->Code = pItem->Code;
					pNewItem->pDate = new DATE2;
					pNewItem->pDate->Day = pItem->pDate->Day;
					pNewItem->pDate->Year = pItem->pDate->Year;
					strcpy_s(pNewItem->pDate->Month, 4, pItem->pDate->Month);
					if(pItem->pNext)
					{
						pNewItem->pNext = new ITEM7;
					}
					else
					{
						pNewItem->pNext = nullptr;
					}
				}
			}
		}
	}
	return *this;
}


