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
EXAM** MySession(int* pnExams);
 int main()
 {
	 int nExams; // the value of this variable (i.e. number of exams) is set by function MySession
	 EXAM** ppMyExams = MySession(&nExams);
	 double averageMark = 0;
	 for (int i = 0; i < nExams; i++) 
	 {
		 printf("Exam in %s on %d %s %d, mark %d\n", (*(ppMyExams + i))->pSubject, (*(ppMyExams + i))->date.day, (*(ppMyExams + i))->date.month, (*(ppMyExams + i))->date.year, (*(ppMyExams + i))->mark);
		 averageMark += (*(ppMyExams + i))->mark;
	 }
	 for (int i = 0; i < nExams; i++)
	 {
		 free((*(ppMyExams + i))->pSubject);
	 }
	 for (int i = 0; i < nExams; i++)
	 {
		 free((*(ppMyExams + i)));
	 }
	 free(ppMyExams);
	 averageMark = averageMark / nExams;
	 printf("The average mark is %lg", averageMark);
 }
 EXAM** MySession(int* pnExams)
 {
	 printf("Enter the number of exams: ");
	 char line[81];
	 gets_s(line);
	 *pnExams = atoi(line);
	 EXAM** ppExams = (EXAM**)malloc(*pnExams * sizeof(EXAM));
	 for (int i = 0; i < *pnExams; i++)
	 {
		 *(ppExams + i) = (EXAM*)malloc(sizeof(EXAM));
		 printf("Enter the subject of the exam: ");
		 gets_s(line);
		 (*(ppExams + i))->pSubject = (char*)malloc(strlen(line) + 1);
		 strcpy((*(ppExams + i))->pSubject, line);
		 printf("Enter the day of the exam: ");
		 gets_s(line);
		 (*(ppExams + i))->date.day = atoi(line);
		 printf("Enter the month of the exam: ");
		 gets_s(line);
		 strcpy((*(ppExams + i))->date.month, line);
		 printf("Enter the year of the exam: ");
		 gets_s(line);
		 (*(ppExams + i))->date.year = atoi(line);
		 printf("Enter the mark of the exam: ");
		 gets_s(line);
		 (*(ppExams + i))->mark = atoi(line);
	 }
	 return ppExams;
 }
