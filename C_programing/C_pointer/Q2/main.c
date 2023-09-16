/*
 * main.c
 *
 *  Created on: ١٧‏/٠٩‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"

int main ()
{
	char alph[27];
	char  * pt=alph;

	int i;
	for(i=0; i<sizeof(alph)-1;i++)
	{
		*(pt+i)='A'+i;

	}

	for(i=0; i<sizeof(alph)-1;i++)
	{
		printf("%c	",*(pt+i));
		fflush(stdin); fflush(stdout);
	}


	return 0;
}
