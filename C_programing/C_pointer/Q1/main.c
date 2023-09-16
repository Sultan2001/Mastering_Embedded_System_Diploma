/*
 * main.c
 *
 *  Created on: ١٧‏/٠٩‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"

int main ()
{
	int m =29;
	int * pt_m=&m;
	printf("Address of m %p\n",pt_m);
	fflush(stdin); fflush(stdout);
	printf("Value of m : %d\n",m);
	fflush(stdin); fflush(stdout);
	printf("_________________________________\n");
	fflush(stdin); fflush(stdout);
	*pt_m =34;

	printf("Address of m %p\n",pt_m);
	fflush(stdin); fflush(stdout);
	printf("Value of m : %d\n",m);
	fflush(stdin); fflush(stdout);
	printf("_________________________________\n");
	fflush(stdin); fflush(stdout);
	*pt_m =7;
	printf("Address of m %p\n",pt_m);
	fflush(stdin); fflush(stdout);
	printf("Value of m : %d\n",m);
	fflush(stdin); fflush(stdout);
	return 0;
}

