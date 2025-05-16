#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#define SIZE 30


void readFromFile(FILE* fp, char Comps[][SIZE], int* count)
{
	while (fscanf(fp, " %[^\n]", Comps[*count]) != EOF)
	{
		(*count)++;
	}
}

void display(char Comps[][SIZE], int count)
{
	int i;
	printf("The List Of Companies\n-------------------\n");
	for (i = 0; i < count; i++)
	{
		printf("%s\n", Comps[i]);
	}
}

int binarySearch(char Comps[][SIZE], char cSearch[], int i, int* x)
{
	int left = 0;
	int right = i;
	int mid;

	while (left <= right)
	{
		mid = left + (right - left) / 2;
		(*x)++;

		if (strcmp(Comps[mid], cSearch) == 0)
			return mid;

		if (strcmp(Comps[mid], cSearch) > 0)
			left = mid + 1;

		else
			right = mid - 1;

	}
	return -1;
}


int main(void)
{
	FILE* fp = fopen("companies.txt", "r");
	if (fp == NULL)
		printf("Mátate Amigo");
	else
	{
		char Comps[50][SIZE];
		int count = 0;
		char cSearch[50];
		int k = 0;  //number of comparisations
		int result;

		readFromFile(fp, Comps, &count);
		display(Comps, count);
		do {
			printf("Enter a company name to search : ");
			scanf(" %[^\n]", cSearch);

			if (strcmp(cSearch, "end") != 0)
			{
				result = binarySearch(Comps, cSearch, count, &k);

				if (result != -1)
				{
					printf("%s has found at %d. index!\n", cSearch, result);
				}

				else
				{
					printf("%s is not on the list!\n", cSearch);
				}

			}
		} while (strcmp(cSearch, "end") != 0);
	}
	return 0;
}