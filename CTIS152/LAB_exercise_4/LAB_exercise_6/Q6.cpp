#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30


int readFromFile(FILE* fp, char flowers[][20])
{
	int i = 0;

	while (fscanf(fp, " %[^\n]", flowers[i]) != EOF)
		i++;

	return i;
}

void display(char flowers[][20], int number)
{
	int i;
	printf("The List Of Flowers\n-------------------\n");

	for (i = 0; i < number; i++)
		printf("%s\n", flowers[i]);
}


int binarySearch(char flowers[][20], int number, char search[])
{
	int left = 0, right = number - 1;
	int mid;

	while (left <= right)
	{
		mid = (left + right) / 2;

		if (strcmp(flowers[mid], search) == 0)
			return mid;
		else if (strcmp(flowers[mid], search) > 0)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return -1;
}

int main(void)
{

	FILE* fp = fopen("flowers.txt", "r");

	if (fp == NULL)
		printf("xd");
	else
	{
		char flowers[SIZE][20];
		char s_flow[20];
		int num, result;

		num = readFromFile(fp, flowers);
		display(flowers, num);


		do {
			printf("\nEnter a flower name to search (or end to stop searching) : ");
			scanf(" %[^\n]", s_flow);

			if (strcmp(s_flow, "end") != 0);
			{

				result = binarySearch(flowers, num, s_flow);

				if (result != -1)
				{
					printf("\n%s found on index %d in the list.", s_flow, result);
				}
				else
					printf("\n%s couldn't be found!", s_flow);


			}

		} while (strcmp(s_flow, "end") != 0);




	}







	return (0);
}