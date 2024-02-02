#include "stdio.h"
#include "stdlib.h"

int main ()
{
	char line[81];
	printf("Enter text: ");
	gets_s(line);
	if (line[0] > 47 && line[0] < 58)
	{
		printf("The text starts with a digit.");
	}
	else if (line[0] > 64 && line[0] < 91)
	{
		printf("The text starts with an uppercase letter.");
	}
	else if (line[0] > 96 && line[0] < 122)
	{
		printf("The text starts with a lowercase letter.");
	}
	else
	{
		printf("The text starts with a special character.");
	}
	return 0;
}