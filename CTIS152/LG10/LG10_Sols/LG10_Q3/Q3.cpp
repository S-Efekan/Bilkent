#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char month[10];
	char name[40];
	int audience;
}concert_t;




void readFromFile(FILE* fp, concert_t* concert,int size)
{
	for (int i = 0; i < size; i++)
	{
		fscanf(fp,
			"%s %[^0-9] %d",
			(concert + i)->month,
			(concert + i)->name,
			&(concert + i)->audience);
		}
}

void bubbleSort(concert_t*concert,int size)
{
	int pass, k;
	concert_t temp;
	int swap = 0;
	for (pass = 0; pass < size - 1; pass++)
	{
		for (k = 0; k < size - 1 -pass; k++)
		{
			if ((concert + k)->audience < (concert + k + 1)->audience)
			{
				temp = *(concert + k + 1);
				*(concert + k + 1) = *(concert + k);
				*(concert + k) = temp;
				swap = 1;
			}
		}
		if (swap == 0)
			break;
	}
}

void display(concert_t*concert,int size)
{
	printf("Month    Concert                              Audience\n");
	printf("--------------------------------------------------------\n");

	for (int i = 0; i < size; i++)
	{
		printf("%-8s %-37s %5d\n",(concert+i)->month,(concert+i)->name,(concert+i)->audience);
	}
}


int main()
{
	FILE* fp = fopen("concert.txt", "r");

	if (fp == NULL)
		printf("xddd");
	else
	{
		int con_num;
		fscanf(fp, "%d", &con_num);
		concert_t* concert = (concert_t*)malloc(sizeof(concert_t) * con_num);
		
		readFromFile(fp,concert,con_num);

		bubbleSort(concert, con_num);
		display(concert, con_num);
		free(concert);
		fclose(fp);
	}



	return 0;
}