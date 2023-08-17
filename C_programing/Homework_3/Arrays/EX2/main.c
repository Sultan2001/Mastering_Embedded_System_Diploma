/*
 * main.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"


void main()
{
	int count=0;
	int i=0;
	printf("Enter the numbers of data :");
	fflush(stdin); fflush(stdout);
	scanf("%i",&count);
	float nums[count];
	float sum=0;
	for(i=0 ; i<count ; i++)
	{
		printf("Enter number: ");
		fflush(stdin); fflush(stdout);
		scanf("%f",&nums[i]);
		sum+=nums[i];
	}

	printf("Average= %f",sum/count);
	fflush(stdin); fflush(stdout);


}
