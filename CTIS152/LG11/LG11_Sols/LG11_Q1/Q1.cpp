#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#define SIZE 20



void readFile(FILE* fp, int* IDs, int* number)
{
	while (fscanf(fp, "%d", IDs + *number) != EOF)
		(*number)++; // *number+=1
}

int binarySearch(int* IDs, int number, int ID, int* comp)
{
	int top = 0;
	int bottom = number;
	int mid;
	while (top <= bottom)
	{
		mid = top + (bottom - top) / 2;
		*comp = *comp + 1;
		if (IDs[mid] == ID) {
			
			return mid;
		}
		if (IDs[mid] < ID) {
			top = mid + 1;
		}
		else{
			bottom = mid - 1;
		}
	}
	return -1;
}

int main(void)
{
	FILE* fp = fopen("empIDs.txt", "r");

	if (fp == NULL)
		printf("No me cohas la cabeza amigo");
	else
	{
		int IDs[SIZE];
		int comp = 0;
		int number = 0;
		int ID;
		int result;

		readFile(fp, IDs, &number);
		fclose(fp);

		printf("Which ID would you like to search?: ");
		scanf("%d", &ID);

		result = binarySearch(IDs, number - 1, ID, &comp);


		if (result != -1)
		{
			printf("\n%d is found at %d. line\n%d. comparisations.", ID, result, comp);
		}
		else
		{
			printf("\nThe number is NOT found in the empIDS.txt");
		}
	}
	return (0);
}