#include "stdio.h"
#include "stdlib.h"
int main()
{
	int x, y;
	char line[81];
	printf("Type the first integer: ");
	gets_s(line);
	x = atoi(line);
	printf("Type the second integer: ");
	gets_s(line);
	y = atoi(line);
	if (x > y)
	{
		printf("%d is greater than %d", x, y);
	}
	else if (x < y)
	{
		printf("%d is less than %d", x, y);
	}
	else
	{
		printf("%d is equal to %d", x, y);
	}
	return 0;
}