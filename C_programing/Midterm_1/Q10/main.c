/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
int max_ones_in_binary(int num);
int main()
{

	printf("%d \n",max_ones_in_binary(110));
	printf("%d",max_ones_in_binary(14));

	int c[]={1,2,,3,4,5};
}
int max_ones_in_binary(int num)
{
	int count=0;
	int max=0;
	while(num!=0)
	{
		if(num%2 !=0)
		{
			count++;
		}
		else
		{
			if(count>max)
			{
				max=count;
				count=0;
			}

		}

		num/=2;
	}
	return max>count?max:count;
}
