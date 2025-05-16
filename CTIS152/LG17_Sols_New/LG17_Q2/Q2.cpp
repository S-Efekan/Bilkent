#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "stack_struct.h"
#include "queue_struct.h"


void readFromFile(FILE* fp, queue_t* Q, stack_t* S)
{
	if (fp == NULL)
		printf("File error occured!");
	else
	{
		item_t temp;
		int i = 0;
		
		initializeQ(Q);
		initializeS(S);

		while (fscanf(fp, "%d %lf %d", &temp.id, &temp.price, &temp.amount) != EOF)
		{
			if (temp.amount < 100){
			
				Q->item[i].id = temp.id;
				Q->item[i].price = temp.price;
				Q->item[i].amount = temp.amount;
			}
			else {

			}

		}







	}
}




int main(void)
{

	FILE* fp;

	fp = fopen("items.txt", "r");
	queue_t Q;
	stack_t S;


	readFromFile(fp,&Q,&S);











	return (0);
}