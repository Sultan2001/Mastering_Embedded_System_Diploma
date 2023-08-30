/*
 * main.c
 *
 *  Created on: ٣٠‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"

struct scomplex_number{

	float real_num;
	float imag_num;


}n1,n2,sum;
struct scomplex_number sum_complex(struct scomplex_number n1 ,struct scomplex_number n2)
{
	struct scomplex_number s;
	s.imag_num=n1.imag_num +n2.imag_num;
	s.real_num = n1.real_num + n2.real_num;

	return s;
}
int main ()
{
	printf("For 1st complex number\n");
	fflush(stdin); fflush(stdout);
	printf("Enter real and imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f",&n1.real_num ,&n1.imag_num);

	printf("For 2st complex number\n");
	fflush(stdin); fflush(stdout);
	printf("Enter real and imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f",&n2.real_num ,&n2.imag_num);

	sum=sum_complex(n1,n2);

	printf("sum = %.2f + %.2f i ",sum.real_num ,sum.imag_num);
	fflush(stdin); fflush(stdout);
	return 0;
}
