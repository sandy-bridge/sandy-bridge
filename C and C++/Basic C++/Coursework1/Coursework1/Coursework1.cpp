#include "stdio.h"
#include "stdlib.h"
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "string.h"
#include "ICS0017DataSource.h"

char* ValidateID(char* pInput)
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
char GetSecondFirstLetter(ITEM7* pItem) //gets the first letter of the second word in ID
{
	char* pID = pItem->pID;
	for (; *pID != ' '; pID++);
	return *(pID + 1);
}

void PrintDataStructure(HEADER_E* pStructure)
{
	if (!pStructure)
	{
		printf("Data error");
		return;
	}
	int itemCount = 1;
	//p becomes current header
	for (HEADER_E* p = pStructure; p; p = p->pNext) //iterates through linked list.
	{
		ITEM7** ppItems;
		int i;
		for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++) //iterate through array of pointers, all letters of the alphabet
		{
			for (ITEM7* pItem = *(ppItems + i); pItem; pItem = pItem->pNext, itemCount++) //dereference pointer and iterate through linked list
			{
				printf("%d) %s %lu %d %s %d\n",itemCount, pItem->pID, pItem->Code, pItem->pDate->Day, pItem->pDate->Month, pItem->pDate->Year );
			}
		}
	}
}
void ClearDataStructure(HEADER_E* pStructure) //frees all members of header
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
				free(tmp);
			}
		}
		free(ppItems);
	}
}

HEADER_E* RemoveItem(HEADER_E* pStructure, char* pItemID = 0)
{
	pItemID = ValidateID(pItemID);
	if (pItemID == 0 || pItemID == "")
	{
		printf("Item ID not provided or input rules not followed!\n");
		return pStructure;
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
				if(!strcmp(pItemID, (pItem->pID)))
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
		free(pItem->pID);
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
		free(pItem->pID);
		free(pItem->pDate);
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
	return pStructure;
}

HEADER_E* InsertItem(HEADER_E* pStructure, char* pNewItemID = 0)
{
	if (pNewItemID)
	{
		pNewItemID = ValidateID(pNewItemID);
	}
	if (pNewItemID != 0 && pNewItemID != "")
	{
		for (HEADER_E* p = pStructure; p; p = p->pNext)
		{
			ITEM7** ppItems;
			int i;
			for (ppItems = (ITEM7**)p->ppItems, i = 0; i < 26; i++)
			{
				for (ITEM7* pItem = *(ppItems + i); pItem; pItem = pItem->pNext)
				{
					if (!strcmp(pItem->pID, pNewItemID))
					{
						printf("ID already exists in structure!\n");
						return pStructure;
					}
				}
			}
		}
	} else
	{
		return pStructure;
	}
	ITEM7* pNewItem = (ITEM7*)GetItem(7, pNewItemID);
	char letter = *(pNewItem->pID); //get first letter
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
		HEADER_E *pNew = (HEADER_E*)malloc(sizeof(HEADER_E));
		pNew->cBegin = letter;
		pNew->ppItems = (void**)calloc(26, sizeof(ITEM7*));
		if(p->pPrior) //existing header always comes before new if pPrior exists as defined by previous while
		{
			pNew->pPrior = p;
			pNew->pNext = p->pNext;
			p->pNext->pPrior = pNew;
			p->pNext = pNew;
			p = pNew;
		}
		else //first header
		{
			p->pPrior = pNew;
			pNew->pPrior = 0;
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
	while(pStructure->pPrior)
	{
		pStructure = pStructure->pPrior;
	}
	return pStructure;
}

int main()
{
	HEADER_E *p = GetStruct5(7, 30);
	for (int i=0; i<10; i++)
	{
		InsertItem(p);
	}
	char newIDs[][5] = {
		"A K",
		"Z Z",
		"Z K",
		"A Z",
		"A A",
		"Z A",
		"G Z",
		"G A",
		"G K",
		"M A",
		"M Ba",
		"M Bb",
		"M Z" };
	PrintDataStructure(p);
	for (int i = 0; i < 13; i++)
	{
		p = InsertItem(p, newIDs[i]);
	}
	PrintDataStructure(p);
	p = InsertItem(p, (char*)"M Ba");
	p = InsertItem(p, (char*)"Mba");
	for (int i = 0; i < 13; i++)
	{
		p = RemoveItem(p, newIDs[i]);
	}
	PrintDataStructure(p);
	ClearDataStructure(p);
	free(p);
	return 0;
}