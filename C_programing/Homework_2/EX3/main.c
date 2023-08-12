/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

void main()
{

	float num1 , num2 , num3;



	printf("Enter three numbers : ");
	fflush(stdout);  fflush(stdin);
	scanf("%f%f%f",&num1, &num2 , &num3);

	if ((num1 > num2) && (num1>num3) )
	{
		printf("largest number = %f",num1);
	}

	else if ((num3 > num2) && (num3>num1) )
	{
		printf("largest number = %f",num3);
	}
	else if ((num2 > num1) && (num2>num3) )
	{
		printf("largest number = %f",num2);
	}

}
