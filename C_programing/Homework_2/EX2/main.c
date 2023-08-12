/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */
#include "stdio.h"

void main()
{

	char ch;
	int i=0;
for(i=0; i<3 ; i++)
{
	printf("Enter an alphabet : ");
	fflush(stdout);  fflush(stdin);
	scanf("%c",&ch);

	if ((ch >='A' && ch <= 'Z') || (ch >='a' && ch <= 'z') )
	{

		switch (ch)
		{
		case 'a':
		case 'A':
		case 'e':
		case 'E':
		case 'i':
		case 'I':
		case 'o':
		case 'O':
		case 'u':
		case 'U':

			printf("%c is vowel \n",ch);

			break;
		default:
			printf("%c is consonant \n",ch);
			break;



		}

	}

	else
	{
		printf("%c is not alphabet",ch);
	}



}

}


