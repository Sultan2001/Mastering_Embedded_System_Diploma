/*
 * main.c
 *
 *  Created on: ١٨‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

void main()
{
	int row , column;

	printf("Enter rows and column of matrix :");
	fflush(stdin); fflush(stdout);
	scanf("%d%d", &row , &column);

	int a[row][column];
	int a_T[column][row];
	int i=0 , y=0;
	printf("Enter elements of matrix \n");
	fflush(stdin); fflush(stdout);
	for(i=0; i<row ; i++)
	{
		for(y=0; y<column; y++)
		{
			printf("Enter elements a%i%i: ",i+1 , y+1);
			fflush(stdin); fflush(stdout);
			scanf("%i",&a[i][y]);
		}
	}


	printf("Entered  Matrix :\n ");
	fflush(stdin); fflush(stdout);
	for(i=0; i<row ; i++)
	{
		for(y=0; y<column; y++)
		{
			printf("%i	",a[i][y]);
			fflush(stdin); fflush(stdout);



		}
		printf("\n");
		fflush(stdin); fflush(stdout);
	}

	/* find transpose */
	printf("Transpose of Matrix : \n");
	fflush(stdin); fflush(stdout);
	for(i=0;i<column;i++)
	{
		for(y=0; y<row; y++)
		{
			a_T[i][y]=a[y][i];


			printf("%i	",a_T[i][y]);
			fflush(stdin); fflush(stdout);
		}
		printf("\n");
		fflush(stdin); fflush(stdout);
	}
}
