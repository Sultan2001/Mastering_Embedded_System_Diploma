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
	int sum=0;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%i",&num);

	for(i=0; i<=num ; i++)
	{
		sum +=i;

	}
	printf("sum = %i", sum);
}

