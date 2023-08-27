/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
int sum_1_to_100 ();

int  main()
{
	printf("%d",sum_1_to_100());

	return 0;
}
int sum_1_to_100 ()
{
	static int i=0;
	static int sum=0;

	if(i==101)
	{
		return sum;
	}
	sum=sum+i;
	i++;
	return sum_1_to_100();

}
