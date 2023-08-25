/*
 * main.c
 *
 *  Created on: ٢٤‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
int power(int num , int p);
int main()
{

	int base,pow;
	printf("Enter base number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&base);
	printf("Enter power number (positive integer): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&pow);
	printf("%d",power(base,pow));

	return 0;
}
int power(int num , int p)
{
	if (p==0)
	{
		return 1;
	}
	else
	{
		return power(num,p-1)*num;
	}
}
