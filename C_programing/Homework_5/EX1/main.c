/*
 * main.c
 *
 *  Created on: ٢٩‏/٠٨‏/٢٠٢٣
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

void main ()
{
	struct sstudent s1;
	printf("Enter name: ");
	fflush(stdin); fflush(stdout);
	gets(s1.name);
	printf("Enter roll number: ");
	fflush(stdin); fflush(stdout);
	scanf("%i",&s1.roll);
	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%lf",&s1.marks);

	printf("Displaying Information\n");
	fflush(stdin); fflush(stdout);

	printf("name  : %s\n",s1.name);
	fflush(stdin); fflush(stdout);
	printf("Roll  : %i\n",s1.roll);
	fflush(stdin); fflush(stdout);
	printf("marks : %lf\n",s1.marks);
	fflush(stdin); fflush(stdout);

}
