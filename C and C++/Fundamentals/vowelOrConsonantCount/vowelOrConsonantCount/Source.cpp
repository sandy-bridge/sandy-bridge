#include "stdio.h"
#include "conio.h"
#include "ctype.h"

char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'y' };
void vowelCount();
void consonantCount();

int main() {
	while (true){
		printf("Welcome to the vowel or consonat counter!\nPress v to count vowels\nPress c to count consonats\nPress x to exit.\n");
		switch (_getche()) {
		case 'V':
		case 'v':
			vowelCount();
			break;
		case 'C':
		case 'c':
			consonantCount();
			break;
		case 'x':
		case 'X':
			return 0;
		default:
			break;
		}
	}
}
void vowelCount() {
	char sentence[81];
	int count = 0;
	printf("\nType input sentence: ");
	gets_s(sentence);
	for (int i = 0; i < 81; i++) {
		for (int j = 0; j < 5; j++) {
			if (tolower(sentence[i]) == vowels[j]) {
				count++;
			}
		}
	}
	printf("There are %d vowels.\n", count);
}
void consonantCount() {
	char sentence[81];
	int count = 0;
	printf("\nType input sentence: ");
	gets_s(sentence);
	for (int i = 0; i < 81; i++) {
		if (sentence[i] == '\0') {
			break;
		}
		int vowelCount = 0;
		for (int j = 0; j < 6; j++) {
			if ((tolower(sentence[i]) != vowels[j]) && isalpha(sentence[i])) {
				vowelCount++;
			}
		}
		if (vowelCount == 6) {
			count++;
		}
	}
	printf("There are %d consonants.\n", count);
}