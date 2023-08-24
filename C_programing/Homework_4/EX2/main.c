/*
 * main.c
 *
 *  Created on: ٢٤‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
int factorial(int i);

int main ()
{
	int num;

	printf("Enter an positive integer: ");
	fflush(stdin); fflush(stdout);
    scanf("%d",&num);
    printf("Factorial of %d = %d ",num,factorial(num));
    fflush(stdin); fflush(stdout);
	return 0;

}
int factorial(int n)
{
	if (n==1)
	{
		return 1;

	}
	else
	{
		return factorial(n-1)*n;
	}



}
