#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main() {
	double a, b, c, x1, x2;
	char line[81];
	printf("Type coefficient a of a quadratic equation (ax² + bx + c = 0): "); //asks the user for inputs
	gets_s(line);
	a = atof(line);
	printf("Type coefficient b: ");
	gets_s(line);
	b = atof(line);
	printf("Type coefficient c: ");
	gets_s(line);
	c = atof(line);
	if (a == 0){ //if a is 0 the equation is not quadratic
		printf("Invalid entry! Exiting...");
		return 0;
	}
	else if (((b * b) - (4 * a *c)) < 0){
		printf("The equation has no real roots. Exiting..."); ///if the discriminant is less than 0
		return 0;
	}
	else {
		x1 = ((-b + sqrt((b * b) - (4 * a * c))) / (2 * a)); //solve both roots using the quadratic formula
		x2 = ((-b - sqrt((b * b) - (4 * a * c))) / (2 * a));
		printf("The roots of the equation are %lg and %lg.", x1, x2);
		return 0;
	}
}