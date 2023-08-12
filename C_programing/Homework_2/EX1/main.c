/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

void main ()
{
	int number;
	int i=0;
for(i=0 ; i<2 ; i++)
{
	printf("Enter an interger you want to cheak : ");
	fflush(stdin); fflush(stdout);

	scanf("%i",&number);
	if (0==number %2)
	{
		printf("%i is even \n ", number);
	}
	else
	{
		printf("%i is odd \n ", number);
	}


}

}
