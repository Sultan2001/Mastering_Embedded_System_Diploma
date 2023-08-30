/*
 * main.c
 *
 *  Created on: ٣٠‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"
struct distance{

	float feet;
	float inch;
}d1,d2,sum;

int main()
{
	printf("Enter information for 1st distance\n");
	fflush(stdin); fflush(stdout);
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d1.feet);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d1.inch);

	printf("Enter information for 2st distance\n");
	fflush(stdin); fflush(stdout);
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d2.feet);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d2.inch);
	sum.feet=d1.feet +d2.feet;
	sum.inch=d1.inch + d2.inch;

	printf("sum of distances=%.2f \'	%.2f\" ",sum.feet,sum.inch);
	fflush(stdin); fflush(stdout);

	return 0;
}
