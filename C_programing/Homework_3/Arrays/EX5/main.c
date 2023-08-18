/*
 * main.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include"stdio.h"

void main()
{
	int count=0 ,i=0, num;
	printf("Enter no of elements:");
	fflush(stdin); fflush(stdout);
	scanf("%i",&count);
	int a[count];

	for(i=0; i<count;i++)
	{
		scanf("%i",&a[i]);
	}
	printf("Enter the  element to be searched:");
		fflush(stdin); fflush(stdout);
		scanf("%i",&num);

	for(i=0; i<count ; i++)
	{
		if (num==a[i])
		{

			printf("Number found at the location = %i\n",i+1);
			fflush(stdin); fflush(stdout);
			break;
		}
		else if(count-1==i)
		{
			printf("Number not found \n");
			fflush(stdin); fflush(stdout);
		}
	}
}
