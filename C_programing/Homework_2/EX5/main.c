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
for(i=0; i<2 ; i++) // for cheak multi
{
	printf("Enter an alphabet : ");
	fflush(stdout);  fflush(stdin);
	scanf("%c",&ch);

	if ((ch >='A' && ch <= 'Z') || (ch >='a' && ch <= 'z') )
	{
		printf("%c is an alphabet \n",ch);
	}
	else
	{
		printf("%c is not an alphabet \n",ch);
	}



}

}


