#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#pragma warning ( disable : 4996 )

int CharFreq(char*, char);

int main ()
{
	char input[] = "Jesse James";
	char letter = 'e';
	int n = strlen(input);
	char* pName = (char*)malloc(n + 1);
	strcpy(pName, input);
	printf("%s\n", pName);
	printf("The character %c occurs %d times.", letter, CharFreq(pName, letter));
	free(pName);
	return 0;
}
int CharFreq(char* pSource, char letter)
{
	int freq = 0;
	while (1) {
		pSource = strchr(pSource, letter);
		if (pSource == NULL)
		{
			break;
		}
		else
		{
			*pSource = '0';
			freq++;
		}
	}
	return freq;
}