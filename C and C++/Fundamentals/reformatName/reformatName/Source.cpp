#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "time.h"

char* CreateRandomName(int n1, int n2)
{ // n1 – length of given name, n2 – length of family name
	if (n1 <= 0 || n2 <= 0)
	{
		return 0;
	}
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	char* pResult = (char*)malloc(n1 + n2 + 2); // names + space + terminating 0
	for (int i = 0; i < n1; i++)
	{
		*(pResult + i) = alphabet[rand() % 26]; // given name
	}
	*pResult = toupper(*pResult); // must start with uppercase letter
	*(pResult + n1) = ' ';
	for (int i = 0; i < n2; i++)
	{
		*(pResult + n1 + 1 + i) = alphabet[rand() % 26]; // family name
	}
	*(pResult + n1 + 1) = toupper(*(pResult + n1 + 1)); // must start with uppercase letter
	*(pResult + n1 + n2 + 1) = 0; // terminating zero
	return pResult;
}
char* ReformatName(char*);
int main()
{
	srand(time(0));
	char* name = CreateRandomName(5, 5);
	printf("%s\n", name);
	char* formatted = ReformatName((name));
	printf("%s\n", formatted);
	free(name);
	free(formatted);
	return 0;
}
char* ReformatName(char* name)
{
	int size = 1;
	while (1)
	{
		if (*(name + size) == '\0')
		{
			break;
		}
		size++;
	}
	char* pResult = (char*)malloc(size + 2);
	int spaceIndex = 0, lastNameLength = 0, firstNameLength = 0;
	for (int i = 0; i < size; i++)
	{
		if (*(name + i) == ' ')
		{
			spaceIndex = i;
		}
	}
	for (int i = 0; *(name + spaceIndex +1 + i) != '\0'; i++)
	{
		*(pResult + i) = *(name + spaceIndex + 1+ i);
		lastNameLength++;
	}
	*(pResult + lastNameLength) = ',';
	*(pResult + lastNameLength + 1) = ' ';
	for (int i = 0; *(name + i) != ' '; i++)
	{
		*(pResult +lastNameLength + 2 + i) = *(name + i);
		firstNameLength++;
	}
	*(pResult + firstNameLength + lastNameLength + 2) = '\0';
	return pResult;
}
