#include "stdio.h"
#include "stdlib.h"

char *CreateRandomString(int n)
{
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	char *pResult = (char*)malloc(n + 1);
	for (int i = 0; i< n; i++)
	{
		*(pResult + i) = alphabet[rand() % 26];
	}
	*(pResult + n) = 0;
	return pResult;
}
char *Reverse(char*);

char* Reverse(char* input)
{
	int n = 0;
	for (int i = 0; ; i++) {
		if (input[i] == '\0')
			break;
		else
			n++;
	}
	char* reversedString = (char*)malloc(n+1);
	for (int i = 0, j=1; i < n; i++, j++) {
		*(reversedString + i) = *(input + n - j);
	}
	*(reversedString + n) = 0;
	return reversedString;
}
int main()
{
	char* pc, * pd;
	pc = CreateRandomString(6);
	printf("%s\n", pc);
	pd = Reverse(pc);
	printf("%s\n", pd);
	free(pc);
	free(pd);
	return 0;
}