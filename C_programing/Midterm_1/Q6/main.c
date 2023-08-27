/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

int unique_elements(int arr[],int length)
{
	int unique = arr[0];
	for (int i = 1; i < length; i++)
	{
		unique ^= arr[i];
	}
	return unique;
}

int main ()
{
	int a[]={1,2,1,2,3,4,4};
	printf("%d",unique_elements(a,7));
	return 0;
}
