#include "stdio.h"
#include "stdlib.h"

int main() {
	printf("Enter some text: ");
	char line[81];
	gets_s(line);
	char buf[20];
	int n = 0;
	for (int i = 0; i <= 80; i++) {
		if ((line[i] > 47) & (line[i] < 58)) {
			buf[n] = line[i];
			n++;
		}
		else if ((line[i] <= 47 | line[i] >= 58) & (n>0)) {
			buf[n] = '\0';
		}
	}
	int x;
	x = atoi(buf);
	if (x % 2 == 0) {
		printf("%d is even.\n", x);
	}
	else {
		printf("%d is odd.\n", x);
	}
	return 0;
}