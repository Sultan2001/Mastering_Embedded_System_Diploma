/*
 * main.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

void main()
{
	char string[100];

	int i=0 ;

	printf("Enter a string : ");
	fflush(stdin); fflush(stdout);
	for(i=0; i<100; i++)
	{
		scanf("%c",&string[i]);
		if ('\n'==string[i])
		{
			string[i]='\0';

			break;
		}
	}

	printf("Length of string : %i",i);



}
