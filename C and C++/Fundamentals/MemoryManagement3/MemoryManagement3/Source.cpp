#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#pragma warning ( disable : 4996 )

int InsertName(char* pNames, int n, char* pNameToInsert);

int main()
{
	char line[81];
	int length = 1;
	printf("Enter a list of names separated by comma: ");
	scanf("%s", line);
	for (int i = 0; i<80; i++)
	{
		if (line[i] == '\0')
		{
			break;
		}
		else
		{
			length++;
		}
	}
	int listLength = length;
	char* pNameList = (char*)malloc(length);
	memmove(pNameList, line, length);
	printf("Enter a new name to insert: ");
	scanf("%s", line);
	length = 1;
	for (int i = 0; i < 80; i++)
	{
		if (line[i] == '\0')
		{
			break;
		}
		else
		{
			length++;
		}
	}
	char* pNewName = (char*)malloc(length);
	memmove(pNewName, line, length);
	char* tempNames = (char*)realloc(pNameList, length + listLength + 1);
	pNameList = tempNames;
	
	if (InsertName(pNameList, listLength, pNewName)) {
		free(pNameList);
		return 0;
	}
	free(pNameList);
	return 0;
}
int InsertName(char* pNames, int n, char* pNameToInsert) {
	int nameLength = 0;
	for (int i = 0; i < 80; i++)
	{
		if (*(pNameToInsert + i) == '\0')
		{
			break;
		}
		else
		{
			nameLength++;
		}
	}
	*(pNameToInsert + nameLength) = ',';
	memmove(pNames + nameLength +1, pNames, n);
	memmove(pNames, pNameToInsert, nameLength +1);
	free(pNameToInsert);
	printf("%s", pNames);
	return 1;
}