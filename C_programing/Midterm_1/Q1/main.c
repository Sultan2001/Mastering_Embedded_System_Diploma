/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
int sum_digits(int num);
int main ()
{

	printf("%d\n",sum_digits(123));  /*  6  */
	fflush(stdin); fflush(stdout);
	printf("%d",sum_digits(1234));  /*  10 */
	fflush(stdin); fflush(stdout);

	return 0;
}
int sum_digits(int num)
{
	int sum=0;
	int temp;
	while (num!=0)
	{
		temp = num%10;
		sum=temp + sum;
		num/=10;
	}

	return sum;

}
