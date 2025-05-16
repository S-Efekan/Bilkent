#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>





void crateBinaryFile(FILE* fp)
{
	srand(time(NULL));
	int num;
	int i = 0;
	while (i < 250)
	{
		num = rand() % 5000 + 1;
		fwrite(&num, sizeof(int), 1, fp);
	}

}

int main()
{
	FILE* fp = fopen("numbers.bin", "wb");
	int nums[250];


	crateBinaryFile(fp);

	fclose(fp);
	fp = fopen("numbers.bin", "rb");

	int count;
	int num;

	printf("How many numbers do you want to read?: ");
	scanf("%d", &count);

	for (int i = 0; i < count; i++)
	{
		fread(&num, sizeof(int), 1, fp);
		printf("%d.  %d", i + 1, num);
	}

}