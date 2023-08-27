/*
 * main.c
 *
 *  Created on: ٢٧‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
double squrt(int num);
int main ()
{
	printf("%f\n",squrt(4));
	fflush(stdin); fflush(stdout);
	printf("%f",squrt(10));
	fflush(stdin); fflush(stdout);
	return 0;
}
double squrt(int num)
{
	float i=0;
	float step = (num/2.0)/200.0;
	while(i < ((float)num/2))
	{
		if(i*i >= num)
			break;
		i+=step;
	}
	return (i);

}
