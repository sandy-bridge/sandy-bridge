#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#pragma warning ( disable : 4996 )

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
int* CharFreqs(char* pSource)
{
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0;; i++)
	{
		if (*(pSource + i) == '\0')
		{
			break;
		}
		*(pSource +i) = tolower(*(pSource+ i));
	}
	int* CharFreqs = (int*)malloc(26 * sizeof(int));
	for (int i = 0; i<26; i++)
	{
		*(CharFreqs + i) = CharFreq(pSource, alphabet[i]);
	}
	return CharFreqs;

}
int main ()
{
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	char name[] = "Butch Cassidy";
	int* count = CharFreqs(name);
	for (int i = 0; i < 26; i++)
	{
		printf("%c - %d\n", alphabet[i], *(count + i));
	}
	free(count);
	return 0;
}