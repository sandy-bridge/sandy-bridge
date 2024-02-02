#include "stdio.h"
#include "stdlib.h"

int main (){
	int i;
	printf("Enter an integer: ");
	char line[81];
	gets_s(line);
	i = atoi(line);
	if ((i % 2) == 0) {
		printf("The integer is even.");
	}
	else {
		printf("The integer is odd.");
	}
	return 0;
}