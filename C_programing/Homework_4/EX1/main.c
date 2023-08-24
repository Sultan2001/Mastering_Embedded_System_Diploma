/*
 * main.c
 *
 *  Created on: ٢٤‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
int  is_prim_Number(int num);


int main()
{
	int num;
	int n1 , n2;
	printf("Enter two numbers (intervals): ");
	fflush(stdin); fflush(stdout);
	scanf("%d%d",&n1,&n2);
	printf("Prime numbers between %d and %d : ",n1,n2);
	fflush(stdin); fflush(stdout);
	num=n1;
	int range =n2-n1;
	while(range--)
	{

	if (is_prim_Number(num++))
	{
		printf("%d ",	num-1);
	}

	}

	return 0;
}



int  is_prim_Number(int num)
{
	int ret=1;
	int i;

	for (i=num-1; i>=2;i--)
	{

		if ((num%i) == 0)
		{
			ret =0;
			break;
		}

	}


	return ret;
}
