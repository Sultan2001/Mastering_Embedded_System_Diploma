/*
 * main.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

int  main()
{

	float a [2][2];
	float b [2][2];

	float sum [2][2];
 int i=0;
 int y=0;


 printf("Enter the elements of 1st matrix \n");
 fflush(stdin);  fflush(stdout);
	for ( i=0 ; i<2 ; i++)
	{
		for (y=0 ; y<2 ; y++)
		{
			printf("Enter a %d%d : ", i+1,y+1);
			fflush(stdin);  fflush(stdout);
			scanf("%f",&a[i][y]);

		}

	}

printf("Enter the elements of 2st matrix \n");
	 fflush(stdin);  fflush(stdout);
	for ( i=0 ; i<2 ; i++)
	{
		for (y=0 ; y<2 ; y++)
		{
			printf("Enter b %d%d : ", i+1,y+1);
			fflush(stdin);  fflush(stdout);
			scanf("%f",&b[i][y]);

		}

	}

	 printf("Sum of  matrix: \n");
	 fflush(stdin);  fflush(stdout);
	for ( i=0 ; i<2 ; i++)
	{
		for (y=0 ; y<2 ; y++)
		{
			printf("%f	", a[i][y] + b[i][y]);
			fflush(stdin);  fflush(stdout);


		}

		printf("\n");
		fflush(stdin);  fflush(stdout);


	}





	return 0;
}
