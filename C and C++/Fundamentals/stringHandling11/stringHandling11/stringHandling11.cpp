#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#pragma warning ( disable : 4996)
int WordFreq(char* pSource)
{
	int freq = 0;
	if (*(pSource) == '\0')
	{
		return 0;
	}
	while (1) {
		pSource = strchr(pSource, ' ');
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
	return (freq +1);
}

int main()
{
	printf("Enter input text: ");
	char line[81];
	gets_s(line);
	int n = strlen(line);
	char* pInput = (char*)malloc((n + 1) * sizeof(char));
	strcpy(pInput, line);
	int words = WordFreq(pInput);
	printf("This text contains %d words.", words);
	free(pInput);
	return 0;
}