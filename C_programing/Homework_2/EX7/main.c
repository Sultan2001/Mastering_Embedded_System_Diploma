/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

void main ()
{
	int num;
	int i=0;
	int fac=1;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%i",&num);
	if (num>=0)
	{
		for(i=1; i<=num ; i++)
		{
			fac *=i;

		}
		printf("Factorial = %i", fac);

	}
	else
	{
		printf("Error!!! Factorial of nagative number doesn't exist\n");
	}
}
