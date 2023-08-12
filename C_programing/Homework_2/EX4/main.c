/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

void main()
{
	float num;
	int i;
	for(i=0; i<3 ; i++)
	{
	printf("Enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&num);
	if(num > 0)
	{
		printf("%f is positive\n",num);
	}
	else if(num < 0)
	{
		printf("%f is negative\n",num);
	}
	else if(0 == num)
	{
		printf("%f is zero\n",num);
	}

}
}
