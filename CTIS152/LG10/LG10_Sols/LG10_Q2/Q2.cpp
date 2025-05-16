#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

void display(char teams[][40],int size)
{
	printf("Football Team List\n------------------------------\n");
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", teams[i]);
	}
}


int main()
{
	char teams[10][40];
	int i = -1;
	do
	{
		i++;
		printf("\nEnter a football team name (finish to stop): ");
		scanf(" %[^\n]", teams + i);
		
	} while (strcmp(*(teams + i), "finish") != 0);

	int pass, k;
	char temp[100];
	for (pass = 1; pass < i - 1; pass++)
	{
		for (k = 0; k < i - pass; k++)
		{
			if (strcmp(teams[k], teams[k + 1]) < 0)
			{
				strcpy(temp, teams[k]);
				strcpy(teams[k], teams[k + 1]);
				strcpy(teams[k + 1], temp);
			}
		}
	}
	display(teams, i);

	return 0;
}