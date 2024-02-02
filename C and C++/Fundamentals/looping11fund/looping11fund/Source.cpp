#include "stdio.h"
#include "stdlib.h"
int main()
{
    printf("enter some text: ");// 48 kuni 57 numbrid,
    char buf[21];
    char line[81];
    gets_s(line);
    int z = 0;
    for (int i = 0; i < 80; i++)
    {
        if (line[i] > 47 && line[i] < 58)
        {
            buf[z] = line[i];
            z++;
        }
        else if (line[i] == ' ' && z > 0)
        {
            buf[z] = '\0';
            break;
        }

    }
    int x = atoi(buf);
    if (x % 2 == 0)
    {
        printf("%d is an even number", x);
    }
    else
    {
        printf("%d is odd", x);
    }
    return 0;
}