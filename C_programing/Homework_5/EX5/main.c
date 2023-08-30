/*
 * main.c
 *
 *  Created on: ٣٠‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"
#include "math.h"
#define AREA_OF_CIRCLE(r)  (M_PI * r*r)

int main ()
{
	float r;
	printf("Enter the radius :");
	fflush(stdin); fflush(stdout);
	scanf("%f",&r);
	printf("Area= %.3f",AREA_OF_CIRCLE(r));


	return 0;

}
