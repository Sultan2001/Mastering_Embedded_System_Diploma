/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
void rev_array(int arr[] ,int size);
int main()
{
	int i=0;
	int a[5]={1,2,3,4,5};
	rev_array(a,5);
	/*  print array_rev */
	for(i=0 ; i<5 ; i++ )
	{
		printf("%d	",a[i]);
	}


	return 0;
}
void rev_array(int arr[] ,int size)
{
	int ar_rev[size];
	int i=0;
	int j=0;
	for(i=0, j=size-1 ; i<size ; i++ , j--)
	{
		ar_rev[i]=arr[j];
	}
	for(i=0 ; i<size ; i++ )
	{
		arr[i]=ar_rev[i];
	}

}
