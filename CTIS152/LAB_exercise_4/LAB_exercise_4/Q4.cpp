#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main(void)
{

	char ISBN[14];
	int cleanISBN[10];


	printf("Enter an ISBN nuber: ");
	scanf("%s", ISBN);

	int i,k = 0;
	int count = 0;
	int total = 0;

	for (i = 0; i < 13; i++)
		if (ISBN[i] <= '9' && ISBN[i] >= '0')
		{
			cleanISBN[k] = (ISBN[i] - '0');
			k++;
		}

	printf("Code  Weight	Weighted Value\n************************\n");
	for (i = 0; i < 10; i++)
	{
		printf("%d	%d	%d\n", cleanISBN[i], 10 - i, cleanISBN[i] * (10 - i));
		total = total + cleanISBN[i] * (10 - i);
	}


	printf("Weighted sum : %d\n", total);
	if (total % 110 == 0)
	{
		printf("\nThe given ISBN is valid!");
	}
	else
	{
		printf("\nThe given ISBN is NOT valid!");
	}

	return (0);
}