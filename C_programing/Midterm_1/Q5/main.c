/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
int count_of_ones_in_binary(int num);
int main()
{
	printf("%d\n",count_of_ones_in_binary(5));
	printf("%d",count_of_ones_in_binary(15));

	return 0;
}
int count_of_ones_in_binary(int num)
{
	int count=0;
	while(num!=0)
	{
		if(num%2 !=0)
		{
			count++;
		}

		num/=2;
	}
	return count;
}
