/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */



#include "stdio.h"

void main ()
{
	int num1;
	int num2;
	printf("Enter two integers:");
	fflush(stdin); fflush(stdout);
	scanf("%d%d",&num1,&num2);
	printf("sum:%d", num1+num2);
}
