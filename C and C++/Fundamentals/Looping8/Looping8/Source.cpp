#include "stdio.h"
#include "conio.h"

int main() {
	char text[21];
	for (int i = 0; i < 20; i++) {
		if (i == 19) {
			text[i] = '\0';
			break;
		}
		char c = _getche();
		if (c == 27) {
			text[i] = '\0';
			break;
		}
		else {
			text[i] = c;
		}
	}
	printf("\r\nThe result is: %s\n ", text);
	return 0;
}