#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char surname[20];
	char name[20];
	int birth;
}people_t;


void swapStruct(people_t* a, people_t* b)
{
	people_t temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void bubbleSortTwoLevel(people_t* people, int size)
{
	int pass, k;

	for (pass = 0; pass < size - 1; pass++)
	{
		for (k = 0; k < size - pass - 1; k++)
		{
			if (strcmp(people[k].surname, people[k + 1].surname) > 0)
			{
				swapStruct(&people[k], &people[k + 1]);
			}
			else
				if (strcmp(people[k].surname, people[k + 1].surname) == 0)
				{
					if (strcmp(people[k].name, people[k + 1].name) > 0) {
						swapStruct(&people[k], &people[k + 1]);
					}
				}
		}
	}
}

void display(people_t* people, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%-15s %-15s %d\n", (people + i)->name, (people + i)->surname, (people + i)->birth);
	}
}


int main(void)
{
	FILE* fp = fopen("people.txt", "r");
	if (fp == NULL)
		printf("xddd try again but it wont work");
	else
	{
		people_t people[12];
		int i = 0;
		while (fscanf(fp, "%s %s %d", people[i].name, people[i].surname, &people[i].birth) != EOF)
			i++;
		bubbleSortTwoLevel(people, i);
		display(people, i);
		fclose(fp);
	}
	return 0;
}