#include "stdio.h"
#include "stdlib.h"
#define SUCCESS 0
#define ZERO_OR_NEGATIVE 1
#define TOO_LARGE 2

int RandVal[100];
int errorNumber;
int GetRandArray(int);

int main() {
	int quantity, max;
	char line[81];
	printf("How many random numbers would you like to find?: ");
	gets_s(line);
	quantity = atoi(line);
	max = GetRandArray(quantity);
	if (errorNumber == ZERO_OR_NEGATIVE) {
		printf("Quantity is zero or less! Exiting");
		return 0;
	}
	else if (errorNumber == TOO_LARGE) {
		printf("Quantity too large! Exiting");
		return 0;
	}
	else {
		printf("The largest number is %d", max);
		return 0;
	}
}

int GetRandArray(int q) {
	int max = 0;
	if (q <= 0) {
		errorNumber = ZERO_OR_NEGATIVE;
		return 0;
	}
	else if (q > 100) {
		errorNumber = TOO_LARGE;
		return 0;
	}
	else {
		for (int i = 0; i < q; i++) {
			RandVal[i] = rand();
		}
		for (int i = 0; i < q; i++) {
			if (max < RandVal[i]) {
				max = RandVal[i];
			}
		}
		return max;
	}
}