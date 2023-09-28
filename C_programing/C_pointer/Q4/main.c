/*
 * main.c
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

int main ()
{
int  arr[15];
int * pt_arr=arr;
int num=0;
printf("number of elements to store in the array (max 15) :");
fflush(stdin); fflush(stdout);
scanf("%d",&num);

int i=0;
for(i=0; i<num; i++)
{
	printf("element - %i : ",i+1);
	fflush(stdin); fflush(stdout);
	scanf("%d",pt_arr++);

}

printf("the element of array in reverse order are :\n");
fflush(stdin); fflush(stdout);
for(i=num; i>0; i--)
{
	printf("element - %i : %d\n",i,*(--pt_arr));
	fflush(stdin); fflush(stdout);


}

	return 0;
}
