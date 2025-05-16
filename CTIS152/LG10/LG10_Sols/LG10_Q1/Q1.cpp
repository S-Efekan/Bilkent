#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


int main()
{

	int labs[15] = { 0 };

	FILE* fp = fopen("labs.txt", "r");
	if (fp == NULL)
		printf("Xd");
	else
	{
		int i = 0;

		while (fscanf(fp, "%d", labs + i) != EOF)
			i++;
		int flag;
		int k, pass;
		for (pass = 1; pass <= i - 1; pass++)
		{
			flag = 1;
			for (k = 0; k < i - pass; k++)
			{
				if (labs[k] > labs[k + 1])
				{
					swap(&labs[k], &labs[k + 1]);
					flag = 0;
				}
			}
			if (flag == 0)
				break;
		}
		for (k = 0; k < i; k++)
		{
			printf("%d\n", labs[k]);
		}


	}



	return 0;
}