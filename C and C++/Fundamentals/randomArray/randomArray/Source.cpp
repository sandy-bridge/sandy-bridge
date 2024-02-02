#include "stdio.h"
#include "stdlib.h"

int main()
{
	int Rand[50];
	int r, max = 0;
	for (int i = 0; i < 49; i++)
	{
		r = rand();
		Rand[i] = r;
	}
	for (int i = 0; i < 49; i ++)
	{
		if (max < Rand[i])
		{
			max = Rand[i];
		}
		else continue;
	}
	printf("%d", max);
	return 0;
}