#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	FILE* fp = fopen("nums.bin", "rb");
	
	if (fp == NULL)
		printf("Matade");
	else
	{
		/*fseek(fp, 0, SEEK_END);
		int size;
		size = ftell(fp) / sizeof(int);
		*/
		int num;
		int count = 0;
		fread(&num, sizeof(int), 1,fp);
	
		while (!feof(fp))
		{
			printf("%d ", num);
			fread(&num, sizeof(int), 1, fp);
			count++;
		}
		printf("\n\nThere are %d number", count);
	}










	return (0);
}