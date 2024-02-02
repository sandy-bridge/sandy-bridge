#include "stdio.h"
#define SUCCESS 0
#define ZERO_OR_NEGATIVE 1

int errorNumber;
char Table[5][5];
void TableFill(int, int);

int main() {
	TableFill(5, 5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%c", Table[i][j]);
		}
		printf("\n");
	}
	return 0;
}
void TableFill(int width, int length) {
	if ((width <= 0) || (length <= 0)) {
		errorNumber = ZERO_OR_NEGATIVE;
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			if (i == j) {
				Table[i][j] = '*';
			}
			else if (i < j) {
				Table[i][j] = '+';
			}
			else {
				Table[i][j] = '-';
			}
		}
	}
}
