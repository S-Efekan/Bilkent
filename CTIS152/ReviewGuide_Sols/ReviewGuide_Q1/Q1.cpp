#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

typedef struct
{
	char name[20];
	int age;
	double cpa;
}stu_t;




void dispayContent(FILE*fp,stu_t*students,int cursor)
{




}


int main()
{
	int choice = 0;

	FILE* fp = fopen("stu.bin","rb");
	
	if (fp == NULL)
		printf("File error!");
	else
	{
		fseek(fp, 0, SEEK_END);
		int total;
		total = ftell(fp) / sizeof(stu_t);
		
		int cursor = 0;
		int x = -1;
		
		
		
		
		do {
			printf("1) Go to record X from top\n");
			printf("2) Move X records ahead\n");
			printf("3) Go X records back from bottom\n");
			printf("4) Exit\n");
			printf("\nEnter your choice: ");
			scanf("%d", &choice);

			if (choice == 1)
			{
				printf("Enter value of X:");
				scanf("%d", &x);
				if (x >= 1 && x <= total)
				{
					cursor = x - 1;
					dispayContent();
				}
				else
					printf("\nInvalid number!!");
			}

			if (choice == 2)
			{
				printf("Enter X: ");
				scanf("%d", &x);
				if (cursor + x < total)
				{
					cursor = cursor + x;
					dispayContent();

				}
				else
					printf("\nOut of limit!");
			}

			if (choice == 3)
			{
				printf("Enter X: ");
				scanf("%d", &x);
				if (x <= total)
				{
					cursor = total - x;
					dispayContent();
				}
				else
					printf("Out of limit!");
			}
		} while (choice != 4);
		fclose(fp);
	}
	return (0);
}