/* LG11_Q1 -> Numeric Binary Search */

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#define MAX 20

//Searches the sale given by the user in the sales list
int binarySearch(int ar[], int top, int bottom, int num, int *comp);
int readFromFile(FILE *inp, int arr[]);

int main(void)
{
	FILE *inp;
	int arr[MAX];
	int size = 0, status, search, index, comp;

	//open points file
	inp = fopen("empIDs.txt", "r");

	//check file
	if (inp == NULL)
		printf("Error in opening file");
	else
	{
		size = readFromFile(inp, arr);

		//get the value to search
		printf("Enter value to find : ");
		scanf("%d", &search);

		comp = 0;
		index = binarySearch(arr, 0, size - 1, search, &comp);

		if (index == -1)
			printf("The number is NOT found in the empIDS.txt\n");
		else
			printf("%d is found at %d. line\n", search, index + 1);

		printf("%d comparisons.\n", comp);

		fclose(inp);
	}
	return(0);
}

int readFromFile(FILE *inp, int arr[])
{
	int status, size = 0;

	//read file content
	status = fscanf(inp, "%d", &arr[size]);

	while (status != EOF && size < MAX)
	{
		size++;
		status = fscanf(inp, "%d", &arr[size]);
	}
	return size;
}

int binarySearch(int ar[], int top, int bottom, int num, int *comp)
{
	int middle;
	while (top <= bottom) {
		middle = (top + bottom) / 2;
		(*comp)++;
		if (num == ar[middle])
			return (middle);
		else
			if (ar[middle] > num)
				bottom = middle - 1;
			else
				top = middle + 1;
	}
	return (-1);
}
