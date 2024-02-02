#include "stdio.h"
#include "stdlib.h"

int main()
{
	int r;
	for (int i = 0; i<50; i++)
	{
		r = rand();
		if (r < 500)
		{
			printf("%d\n", r);
		}
	}
	return 0;
}