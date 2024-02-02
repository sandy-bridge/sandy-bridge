#include "stdio.h"
#include "conio.h"

int main()
{
	char c;
	char text[21];
	for (int i = 0; i < 19; i++)
	{
		c = _getche();
		if (c == 27)
		{
			text[i+1] = '\0';
			break;
		}
		else
		{
			text[i] = c;
		}
	}
	text[20] = '\0';
	printf("\n");
	printf(text);
	return 0;
}