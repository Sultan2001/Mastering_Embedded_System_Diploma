/*
 * main.c
 *
 *  Created on: ٢٥‏/٠٨‏/٢٠٢٣
 *      Author: mohamedsultan
 */

#include "stdio.h"
#include "string.h"
void str_rev(char text [], int len, char rev[]);
int main()
{

	int len=0;
	char text [100];
	char text_rev [100];

	printf("Enter a sentence :");
	fflush(stdin); fflush(stdout);
	gets(text);
	len=strlen(text);
	str_rev(text,len,text_rev);
	printf("%s\n",text_rev);
	fflush(stdin); fflush(stdout);




	return 0;
}
void str_rev(char text [],int len, char rev[])
{
	static int i=0;
	if (len==0)
	{
		rev[i]='\0';
		return;
	}
	/*printf("%c",text[len-1]); */
	rev[i]=text[len-1];
	i++;
	str_rev(text , len-1,rev);
	i=0;

}
