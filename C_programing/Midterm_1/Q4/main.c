/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"

int rev_digits(int num);

int main()
{
	printf("%d\n",rev_digits(2457));
	printf("%d",rev_digits(7501));
	return 0;
}

int rev_digits(int num)
{
	int temp;
	double rev=0;
	double pos=0.1;
	int shift=1;
	for(;num!=0;pos*=0.1 , shift*=10)
	{
		temp=num%10;
		rev=rev + (temp*pos);
		num/=10;
	}
	return (int)(rev*shift);


}
