#include "stdio.h"
#include "stdlib.h"
int main()
{
	int x, y, z;
	char line[81];
	printf("Type the first integer: ");
	gets_s(line);
	x = atoi(line);
	printf("Type the second integer: ");
	gets_s(line);
	y = atoi(line);
	z = x + y;
	printf("The sum is %d", z);
	return 0;
}