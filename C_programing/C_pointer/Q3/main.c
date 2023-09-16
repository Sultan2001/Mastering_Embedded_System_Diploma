/*
 * main.c
 *
 *  Created on: ١٧‏/٠٩‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"
#include "string.h"

int main ()
{
	char str[100]="mohamed sultan";
	char str_rev[100];
	char *ptr_str=NULL;
	printf("Enter string: ");
	fflush(stdin); fflush(stdout);
	gets(str);
	int len=strlen(str);
	ptr_str=str+len-1;
	int i=0;
	for(i=0; i<len; i++)
	{
		str_rev[i]=*ptr_str;
		ptr_str--;
	}
	str_rev[len]='\0';
	printf("%s \n",str_rev);
	fflush(stdin); fflush(stdout);



	return 0;
}

