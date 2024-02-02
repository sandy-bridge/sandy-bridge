#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#pragma warning ( disable : 4996 )

typedef struct Date {
	int day;
	char month[4];
	int year;
} DATE;
typedef struct Exam {
	char* pSubject;
	DATE date;
	int mark;
} EXAM;

EXAM* MySession(int*);

int main()
{
	int nExams;
	EXAM* pMyExams = MySession(&nExams);
	double averageMark = 0;
	for (int i = 0; i<nExams; i++)
	{
		printf("Exam in %s on %d %s %d, mark %d\n", (pMyExams + i)->pSubject, (pMyExams + i)->date.day, (pMyExams + i)->date.month, (pMyExams + i)->date.year, (pMyExams + i)->mark);
		averageMark += (pMyExams + i)->mark;
	}
	averageMark = averageMark / nExams;
	printf("The average mark is %lg", averageMark);
	for (int i = 0; i<nExams; i++)
	{
		free((pMyExams + i)->pSubject);
	}
	free(pMyExams);
	return 0;
}
EXAM* MySession(int* pnExams)
{
	printf("Enter the number of exams: ");
	char line[81];
	gets_s(line);
	*pnExams = atoi(line);
	EXAM* pExams = (EXAM*)malloc(*pnExams * sizeof(EXAM));
	for (int i = 0; i<*pnExams; i++)
	{
		printf("Enter the subject of the exam: ");
		gets_s(line);
		(pExams + i)->pSubject = (char*)malloc(strlen(line) + 1);
		strcpy((pExams + i)->pSubject, line);
		printf("Enter the day of the exam: ");
		gets_s(line);
		(pExams + i)->date.day = atoi(line);
		printf("Enter the month of the exam: ");
		gets_s(line);
		strcpy((pExams + i)->date.month, line);
		printf("Enter the year of the exam: ");
		gets_s(line);
		(pExams + i)->date.year = atoi(line);
		printf("Enter the mark of the exam: ");
		gets_s(line);
		(pExams + i)->mark = atoi(line);
	}
	return pExams;
}