#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "math.h"

double tempConverter (double temp, char unit)
{
	double conversion;
	if (unit == 'F')
	{
		conversion =  (5 * (temp - 32) /9);
	}
	else if (unit == 'C')
	{
		conversion = ((9 *temp )/ 5) + 32;
	}
	return conversion;
}

int main()
{
	double tempIn, tempOut;
	char baseUnit, newUnit;
	char line[81];
	printf("Enter base unit: ");
	gets_s(line);
	baseUnit = line[0];
	baseUnit = toupper(baseUnit);
	printf("Enter temperature to convert: ");
	gets_s(line);
	tempIn = atof(line);
	tempOut = tempConverter(tempIn, baseUnit);
	if (isnan(tempOut))
	{
		printf("No solution.");
		return 0;
	}
	if (baseUnit == 'F')
	{
		newUnit = 'C';
	}
	else if (baseUnit == 'C')
	{
		newUnit = 'F';
	}
	printf("%lg degrees %c is %lg degrees %c", tempIn, baseUnit, tempOut, newUnit);
	return 0;
}