#include "stdio.h"
#include "stdlib.h"

int main()
{
	char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'y' };
	char line[81];
	int vowelCount = 0;
	printf("Enter text: ");
	gets_s(line);
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (line[i] == vowels[j])
			{
				vowelCount += 1;
			}
			else continue;
		}
	}
	printf("There are %d lowercase vowels.", vowelCount);
	return 0;
}