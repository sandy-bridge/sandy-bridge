#include "stdio.h"

void trimSpaces(char[]);
char Buf1[81], Buf2[81];

int main() {

	printf("Enter your text: ");
	gets_s(Buf1);
	trimSpaces(Buf1);
	printf("The compressed text is %s\n", Buf2);
	return 0;
}
void trimSpaces(char source[]) {
	bool space = false;
	int trimmedSpace = 0;
	for (int i = 0; i < 81; i++) {
		if (space == true && source[i] == ' ') {
			trimmedSpace++;
			continue;
		}
		else if (source[i] == ' ') {
			space = true;
		}
		else {
			space = false;
		}
		Buf2[i-trimmedSpace] = source[i];
	}
}