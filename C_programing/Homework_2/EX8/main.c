/*
 * main.c
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

void main()
{
	float num1 , num2, result;

	char op;
	printf("Enter operator either + or - or * or / : ");
	fflush(stdin); fflush(stdout);

	scanf("%c",&op);

	printf("Enter two operands: ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f",&num1,&num2);
	switch (op)
	{

	case '-':
		result=num1 - num2;

		break;
	case '+':
		result= num1+num2;
		break;
	case '*':
		result= num1* num2;
		break;
	case '/':
		result= num1/num2;
		break;
	default :
		printf("invalid operator");
		break;


	}

	printf("%0.3f %c %0.3f = %0.3f",num1,op,num2,result);



}
