/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"
int is_prime_number(int num);
void print_prime_number(int n1 , int n2);
int main ()
{
	print_prime_number(1,20);

	return 0;
}

int is_prime_number(int num)
{
	int i;
	int ret =1;
	for (i=2;(i<num) && (num!=2); i++)
	{
		if((num%i)==0)
		{
			ret=0;
			break;
		}
		ret=1;
	}
	return ret;
}
void print_prime_number(int n1 , int n2)
{

	int i=0;
	for(i=n1; i<=n2 ; i++)
	{
		if (is_prime_number(i))
		{
			printf("%d	",i);
			fflush(stdin); fflush(stdout);

		}

	}

}
