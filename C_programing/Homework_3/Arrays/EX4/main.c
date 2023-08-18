/*
 * main.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include"stdio.h"

void main()
{
	int count=0 ,i=0, num,loc ,temp;
	printf("Enter no of elements:");
	fflush(stdin); fflush(stdout);
	scanf("%i",&count);
	int a[count+1];

	for(i=0; i<count;i++)
	{
		scanf("%i",&a[i]);
	}
	printf("Enter the element to be inserted : ");
	fflush(stdin); fflush(stdout);
	scanf("%i",&num);
	printf("Enter the location : ");
	fflush(stdin); fflush(stdout);
	scanf("%i",&loc);
	loc--; /* because the index start from Zero */
	int a_new[count-loc];

	for(i=loc; i<count ;i++)
	{
		a_new[i-loc]=a[i];

	}
	a[loc]=num;
	for(i=loc; i<count+1 ;i++)
	{
		a[i+1]=a_new[i-loc];

	}

	for(i=0; i<count+1;i++)
	{
		printf("%i	",a[i]);

	}
}
