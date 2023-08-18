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
	char ch;
	int i=0 , freq=0;

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
	printf("Enter a character to find Frequency : ");
		fflush(stdin); fflush(stdout);
	scanf("%c",&ch);
	for (i=0;string[i]!='\0';i++)
	{

		if(ch==string[i])
		{
			freq++;
		}
	}

	printf("\nFrequency of %c = %i\n",ch,freq);




}
