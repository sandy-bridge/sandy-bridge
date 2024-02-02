#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "memory.h"
#include "ctype.h"
#pragma warning (disable : 4996)

typedef struct student {
	char* pName, *pCode;
	int mMathematics, mPhysics, mChemistry;
	double average;
} STUDENT;

STUDENT* Exam(char* pStudents, char* pMathematics, char* pPhysics, char* pChemistry);

char students[] = "John Smith 25156IVSB; Mary Weaver 253742ABB; James Carpenter 252422TAF; Elizabeth Clerk 251443MV"; //name and code
char Mathematics[] = "John Smith 5; Mary Weaver 4; James Carpenter 4; Elizabeth Clerk 2"; //name and mark, order different
char Physics[] = "Mary Weaver 3; John Smith 5; Elizabeth Clerk 2; James Carpenter 2";
char Chemistry[] = "Elizabeth Clerk 4; Mary Weaver 5; John Smith 1; James Carpenter 3";

int main() {
	STUDENT* bStudent = Exam(students, Mathematics, Physics, Chemistry);
	printf("%s %s, average mark %lg", bStudent->pName, bStudent->pCode, bStudent->average);
	free(bStudent->pName);
	free(bStudent->pCode);
	free(bStudent);
	return 0;
}

STUDENT* Exam(char* pStudents, char* pMathematics, char* pPhysics, char* pChemistry) {
	if (!pStudents || !*pStudents || !pMathematics || !*pMathematics || !pPhysics || !*pPhysics || !pChemistry || !*pChemistry) { // check if anything is zero or empty
		return 0;
	}
	int nStudents = 0;
	char* pTemp = pStudents;
	while (pTemp != NULL) { //count number of students by finding semicolons
		pTemp = strchr(pTemp, ';');
		nStudents++; //this method also accounts for the last student
		if (pTemp) {
			pTemp++;
		}
	}
	STUDENT* Students = (STUDENT*)malloc(nStudents * sizeof(STUDENT)); //allocate memory for struct pointer containing all students
	for (int i = 0; i < nStudents; i++, Students++) { //fills names and codes in order of first list
		char* pNameEnd = pStudents, *pCodeEnd;
		for (int j = 0; j < 2; j++) {
			pNameEnd = strchr(pNameEnd, ' '); //finds second space in students
			pNameEnd++;
		}
		pNameEnd--;
		*pNameEnd = 0; //pStudents now only contains the name
		Students->pName = (char*)malloc(strlen(pStudents) + 1);
		strcpy(Students->pName, pStudents);
		pCodeEnd = strchr(pNameEnd+1, ';');
		if(pCodeEnd){ //this is to make it work for the last student
			*pCodeEnd = 0;
		}
		Students->pCode = (char*)malloc(strlen(pNameEnd + 1) + 1); //pNameEnd is now the code
		strcpy(Students->pCode, pNameEnd + 1);
		if (pCodeEnd) {
			memmove(pStudents, pCodeEnd + 2, strlen(pCodeEnd + 2) + 1); //moves everything forward, +2 accounts for space and semicolon
		}
	}
	Students -= (nStudents); //restores pointer to original location
	for (int i = 0; i < nStudents; i++, Students++) { //adds mathematics grades, next 2 are similar
		char* mark = strstr(pMathematics, Students->pName);
		bool semicolon = false;
		for (int i = 0; ; i++) {
			if (isdigit(*(mark + i))) { //finds location of number
				mark = mark + i;
				break;
			}
		}
		if (*(mark + 1) == ';') { //this is to restore the semicolon and for atoi to work
			semicolon = true;
			*(mark + 1) = 0;
		}
		Students->mMathematics = atoi(mark);
		if (semicolon) {
			*(mark + 1) = ';';
		}
	}
	Students -= (nStudents);
	for (int i = 0; i < nStudents; i++, Students++) {
		char* mark = strstr(pPhysics, Students->pName);
		bool semicolon = false;
		for (int i = 0; ; i++) {
			if (isdigit(*(mark + i))) {
				mark = mark + i;
				break;
			}
		}
		if (*(mark + 1) == ';') {
			semicolon = true;
			*(mark + 1) = 0;
		}
		Students->mPhysics = atoi(mark);
		if (semicolon) {
			*(mark + 1) = ';';
		}
	}
	Students -= (nStudents);
	for (int i = 0; i < nStudents; i++, Students++) {
		char* mark = strstr(pChemistry, Students->pName);
		bool semicolon = false;
		for (int i = 0; ; i++) {
			if (isdigit(*(mark + i))) {
				mark = mark + i;
				break;
			}
		}
		if (*(mark + 1) == ';') {
			semicolon = true;
			*(mark + 1) = 0;
		}
		Students->mChemistry = atoi(mark);
		if (semicolon) {
			*(mark + 1) = ';';
		}
	}
	Students -= (nStudents);
	for (int i = 0; i < nStudents; i++, Students++) { //calculates average grade for each student
		Students->average = ((double)(Students->mPhysics) + (double)(Students->mMathematics) + (double)(Students->mChemistry)) / (double)3;
	}
	Students -= (nStudents);
	double maxaverage = 0;
	for (int i = 0; i < nStudents; i++, Students++) { //finds highest average
		if (maxaverage < Students->average) {
			maxaverage = Students->average;
		}
	}
	Students -= (nStudents); 
	STUDENT* bStudent = (STUDENT*)malloc(sizeof(STUDENT));
	for (int i = 0; i < nStudents; i++, Students++) { //copying elements one by one because C is a dick
		if (maxaverage == Students->average) {
			bStudent->pName = (char*)malloc(strlen(Students->pName) + 1);
			strcpy(bStudent->pName, Students->pName);
			bStudent->pCode = (char*)malloc(strlen(Students->pCode) + 1);
			strcpy(bStudent->pCode, Students->pCode);
			bStudent->mChemistry = Students->mChemistry;
			bStudent->mMathematics = Students->mMathematics;
			bStudent->mPhysics = Students->mPhysics;
			bStudent->average = Students->average;
		}
	}
	Students -= (nStudents);
	for (int i = 0; i < nStudents; i++, Students++){ //frees memory for everything in struct
		free(Students->pName);
		free(Students->pCode);
	}
	Students -= (nStudents);
	free(Students);
	return bStudent;
}