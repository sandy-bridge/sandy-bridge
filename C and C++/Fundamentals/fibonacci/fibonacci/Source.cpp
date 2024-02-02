#include "stdio.h"

int main()
{
	int Fib[20] = { 1, 1 };
	for (int i = 2; i <20; i++)
	{
		Fib[i] = Fib[i - 1] + Fib[i - 2];
	}
	for (int i = 0; i < 20; i++)
	{
		printf("%d\n", Fib[i]);
	}
}