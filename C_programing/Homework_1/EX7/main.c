/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"

void main()
{
	float a ;
	float b;

	printf("Enter value of a: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&a);

	printf("Enter value of b: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&b);

	a=a+b;
	b=a-b;
	a=a-b;
	printf("After swapping, value of a = %0.2f\n",a);
	printf("After swapping, value of b = %0.1f\n",b);




}
