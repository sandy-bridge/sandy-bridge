#include "stdio.h"

typedef struct Date
{
	int day;
	char month[4];
	int year;
} DATE;
typedef struct Exam
{
	const char* pSubject;
	DATE date;
	double mark;
} EXAM;

int main() {
	EXAM exams[4];
	exams[0] = { "ICS0004", {18, "Dec", 2020}, 5 };
	exams[1] = { "ICA0013", {14, "Dec", 2020}, 4 };
	exams[2] = { "ICY0001", {17, "Dec", 2020}, 3 };
	exams[3] = { "ICS0001", {21, "Dec", 2020}, 4 };
	for (int i = 0; i<4; i++)
	{
		printf("Exam subject: %s, Date: %d %s %d, mark: %lg\n", exams[i].pSubject, exams[i].date.day, exams[i].date.month, exams[i].date.year, exams[i].mark);
	}
	return 0;
}