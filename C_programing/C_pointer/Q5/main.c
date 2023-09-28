/*
 * main.c
 *
 *  Created on: ٢٩‏/٠٩‏/٢٠٢٣
 *      Author: mohamedsultan
 */


#include "stdio.h"

struct Exmployee{

	char name[50];
	unsigned int id ;

};

int main ()
{
	struct Exmployee p1={"mohamed" , 10};
	struct Exmployee p2={"Ahmed" , 20};
	struct Exmployee p3={"osama" , 30};
	struct Exmployee *pt [3]={&p1,&p2,&p3};

	struct Exmployee **ppt=pt;



	printf("Exmployee Name : %s\n",ppt[0]->name);
	printf("Exmployee ID : %d \n",ppt[0]->id);

	return 0;
}
