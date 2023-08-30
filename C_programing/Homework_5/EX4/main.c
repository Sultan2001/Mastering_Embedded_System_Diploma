/*
 * main.c
 *
 *  Created on: ٣٠‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
#include "string.h"

struct sstudent
{
	char name[50];
	int roll;
	double marks;

};

#define MAX_STUDENT 4
int main ()
{

	struct sstudent s[MAX_STUDENT];
	int i=0;
	printf("Enter information of students:\n");
	fflush(stdin); fflush(stdout);
	for (i=0 ; i<MAX_STUDENT ; i++)
	{
		printf("Enter name: ");
		fflush(stdin); fflush(stdout);
		gets(s[i].name);
		printf("Enter roll number: ");
		fflush(stdin); fflush(stdout);
		scanf("%i",&s[i].roll);
		printf("Enter marks: ");
		fflush(stdin); fflush(stdout);
		scanf("%lf",&s[i].marks);
	}
	printf("Displaying Information\n");
	fflush(stdin); fflush(stdout);

	for (i=0 ; i<MAX_STUDENT ; i++)
	{
		printf("name  : %s\n",s[i].name);
		fflush(stdin); fflush(stdout);
		printf("Roll  : %i\n",s[i].roll);
		fflush(stdin); fflush(stdout);
		printf("marks : %lf\n",s[i].marks);
		fflush(stdin); fflush(stdout);
	}

	return 0;
}
