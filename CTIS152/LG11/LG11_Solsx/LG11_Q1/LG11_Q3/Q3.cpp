/* LG11_Q3 -> Read the file into the structure array then makes binary search */

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30

typedef struct
{
	char phoneName[50];
	int prices;
	int stock;
}phone_t;

int readFromFile(FILE *inp, phone_t arr[]);
void display(phone_t *arr, int n);
int binarySearch(phone_t *arr, int top, int bottom, int n);

int main(void)
{
	FILE *inp;
	inp = fopen("phone.txt", "r");

	if (inp == NULL)
		printf("Error!\n");
	else
	{
		char name[50];
		phone_t *arr;
		int	index,size,n;

		fscanf(inp,"%d",&size);
		arr = (phone_t*)malloc(sizeof(phone_t)*size);
		size = readFromFile(inp, arr);
		fclose(inp);

		display(arr, size);

		printf("\nEnter number of stock to see the campaign: ");
		scanf("%d", &n);

		while (n != -1)
		{
			index = binarySearch(arr, 0, size - 1, n);

			if (index != -1)
				printf("%s found on the %d sale rate %d stock\n", arr[index].phoneName, arr[index].prices,arr[index].stock);
			else
				printf("%d NOT FOUND for the campaign\n", n);

			printf("\nEnter number of stock to see the campaign: ");
			scanf("%d", &n);
		}
	}

	return 0;
}

int readFromFile(FILE *inp,phone_t *arr)
{
	int i = 0, status;

	while (fscanf(inp, " %[^0-9] %d %d", arr[i].phoneName,&arr[i].prices,&arr[i].stock) != EOF && i < SIZE)
		i++;

	return i;
}

void display(phone_t *arr, int size)
{
	printf("      PHONE INFORMATIONS FOR PEOPLE\n");
	printf("-----------------------------------------\n");

	for (int i = 0; i < size; i++)
		printf("%-15s  %7d  %10d\n", arr[i].phoneName,arr[i].prices,arr[i].stock);
}

//binary search function
int binarySearch(phone_t *arr, int top, int bottom, int n)
{
	int middle;
	while (top <= bottom)
	{
		middle = (top + bottom) / 2;

		if (arr[middle].stock==n)
			return (middle);
		else
			if (arr[middle].stock > n)
				bottom = middle - 1;
			else
				top = middle + 1;
	}
	return (-1);
}