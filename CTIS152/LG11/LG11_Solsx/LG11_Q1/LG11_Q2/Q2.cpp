/* LG11_Q2 -> Read the company names from a file into an array and search for a specified company name */

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <string.h>

#define SIZE 30

int readFromFile(FILE *inp, char companies[][SIZE]);
void display(char companies[][SIZE], int n);
int binarySearch(char companies[][SIZE], int top, int bottom, char srchComp[]);

int main(void)
{
	FILE *inp;
	inp = fopen("companies.txt", "r");

	if (inp == NULL)
		printf("Error!\n");
	else
	{
		char companies[SIZE][SIZE],
			srchComp[SIZE];
		int	index,
			noOfComp;

		noOfComp = readFromFile(inp, companies);
		fclose(inp);

		display(companies, noOfComp);

		//get a company name from the user
		printf("\nEnter a company name to search (or end to stop searching): ");
		scanf("%[^\n]", srchComp);

		while (strcmp(srchComp, "end") != 0)
		{
			//get the index of searched company name
			index = binarySearch(companies, 0, noOfComp - 1, srchComp);

			if (index != -1)
				printf("%s found on the index %d in the list\n", srchComp, index);
			else
				printf("%s could not be found!\n", srchComp);

			printf("\nEnter a company name to search (or end to stop searching): ");
			scanf("\n%[^\n]", srchComp);
		}
	}

	return 0;
}

int readFromFile(FILE *inp, char companies[][SIZE])
{
	int i = 0, status;

	i = 0;
	status = fscanf(inp, "%[^\n]", companies[i]);

	while (status != EOF && i < SIZE)
	{
		i++;
		status = fscanf(inp, "\n%[^\n]", companies[i]);
	}

	return i;
}

void display(char companies[][SIZE], int noOfComp)
{
	printf("The List of Companies\n");
	printf("-------------------\n");

	for (int i = 0; i < noOfComp; i++)
		printf("%s\n", companies[i]);
}

//binary search function
int binarySearch(char companies[][SIZE], int top, int bottom, char srchComp[])
{
	int middle;
	while (top <= bottom)
	{
		middle = (top + bottom) / 2;

		if (strcmp(companies[middle], srchComp) == 0)
			return (middle);
		else
			if (strcmp(companies[middle], srchComp) < 0)
				bottom = middle - 1;
			else
				top = middle + 1;
	}
	return (-1);
}