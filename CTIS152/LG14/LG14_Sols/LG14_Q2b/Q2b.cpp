#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp = fopen("nums.bin", "rb");

	if (fp == NULL)
		printf("Matade");
	else
	{
		int size;
		int num;

		fseek(fp, 0, SEEK_END);
		size = ftell(fp) / sizeof(int);

		int* arr = (int*)malloc(sizeof(int) * size);

		int i = 0;

		rewind(fp);

		while (!feof(fp))
		{
			fread(arr+i, sizeof(int), 1, fp);
			i++;
		}

		for (i = 0; i < size; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\nThere are %d numbers", size);




	}
	return (0);
}