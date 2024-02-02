#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "memory.h"
#include "ctype.h"
#pragma warning ( disable : 4996 )

typedef struct
{
	int day;
	char month[4];
	int year;
} DATE;

typedef struct
{
	const char* pFirstName, * pLastName, * pNationality;
	DATE Birthdate;
} STUDENT;
int Exam(STUDENT* pStudents, int nStudents, const char* pPattern);

STUDENT students[] = { {"John","Smith","Britain", {1, "Feb", 2000}},  {"Mary","Weaver","USA", {2, "Mar", 2001}},  {"James","Carpenter","Canada", {11, "Oct", 2002}},  {"Elizabeth","Clerk","Ireland", {21, "Dec", 2001}} };
const char* ptoSearch = "Carpenter, James born 11 October 2002 from Canada";

char* LastName(char* pPattern) {
	char* pComma = strchr(pPattern, ',');
	*pComma = 0;
	char* pLastName = (char*)malloc(strlen(pPattern) + 1);
	strcpy(pLastName, pPattern);
	memmove(pPattern, pComma + 2, strlen(pComma + 2) + 1); //+2 to account for comma and space
	return pLastName;
}
char* FirstName(char* pPattern) {
	char* pSpace = strchr(pPattern, ' ');
	*pSpace = 0;
	char* pFirstName = (char*)malloc(strlen(pPattern) + 1);
	strcpy(pFirstName, pPattern);
	memmove(pPattern, pSpace + 1, strlen(pSpace + 1) + 1);
	return pFirstName;
}
char* Date(char* pPattern) { //finds first and last digit of pPattern
	char* pEnd = 0, *pStart = 0, temp;
	for (int i = strlen(pPattern) - 1; i >= 0; i--) {
		if (isdigit(*(pPattern + i))) {
			temp = *(pPattern + i);
			pEnd = pPattern + i;
			break;
		}
	}
	*(pEnd + 1) = '\0';
	for (int i = 0; i <= strlen(pPattern) - 1; i++) {
		if (isdigit(*(pPattern + i))) {
			pStart = pPattern + i;
			break;
		}
	}
	char* pDate = (char*)malloc(strlen(pStart) + 1);
	strcpy(pDate, pStart);
	*(pEnd + 1) = temp;
	return pDate;
}
int Day(char* pDate) {
	char* cDay = FirstName(pDate); //first name function finds by space so i use this
	int Day = atoi(cDay);
	return Day;
}
char* Nationality(char* pPattern) {
	char* pSpace = strrchr(pPattern, ' ');
	*pSpace = 0;
	char* pNationality = (char*)malloc(strlen(pSpace + 1) + 1);
	strcpy(pNationality, (pSpace +1));
	return pNationality;
}
int main() {
	printf("%d\n", Exam(students, 4, ptoSearch));
	return 0;
}
int Exam(STUDENT* pStudents, int nStudents, const char* pPattern) {
	int returnValue = 0;
	STUDENT toSearch;
	if (!pStudents || !pPattern) { //input pointers must not be 0
		return returnValue;
	}
	else if (pPattern=="") { //must not point to emtpy string
		return returnValue;
	}
	else if (nStudents == 0) { //number of students must not be 0
		return returnValue;
	}
	char* tpPattern = (char*)malloc(strlen(pPattern) + 1);
	strcpy(tpPattern, pPattern);
	toSearch.pLastName = LastName(tpPattern);
	toSearch.pFirstName = FirstName(tpPattern);
	char* pDate = Date(tpPattern);
	toSearch.Birthdate.day = Day(pDate);
	strncpy(toSearch.Birthdate.month, FirstName(pDate), 3); //firstname function finds by space, using it again
	toSearch.Birthdate.month[3] = '\0';
	toSearch.Birthdate.year = atoi(pDate); //pdate now only contains year
	toSearch.pNationality = Nationality(tpPattern);
	free(pDate);
	free(tpPattern);
	for (int i = 0; i < nStudents; i++, pStudents++) { //strcmp because == didn't work
		if (!strcmp((pStudents->pFirstName), (toSearch.pFirstName)) &&\
			!strcmp((pStudents->pLastName), (toSearch.pLastName)) &&\
			!strcmp((pStudents->pNationality), (toSearch.pNationality)) &&\
			!strcmp((pStudents->Birthdate.month), (toSearch.Birthdate.month)) &&\
			(pStudents->Birthdate.day == toSearch.Birthdate.day) &&\
			(pStudents->Birthdate.year == toSearch.Birthdate.year)){
			returnValue = 1;
		}
	}
	return returnValue;
}


