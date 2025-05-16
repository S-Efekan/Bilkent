#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char comp[15];
	int price;
	int stock;
}t_phone;

void readFile(FILE* fp, t_phone* phone, int number)
{
	int i;

	for (i = 0; i < number; i++)
	{
		fscanf(fp, "%s %d %d",
			(phone + i)->comp,
			&(phone + i)->price,
			&(phone + i)->stock);
	}
}

void display(t_phone* phone, int number)
{
	printf("	PHONE INFORMATIONS FOR PEOPLE\n");
	printf("-----------------------------------------\n");
	int i;
	for (i = 0; i < number; i++)
	{
		printf("%s	%d	%d\n", (phone + i)->comp, (phone + i)->price, (phone + i)->stock);
	}
}

int binarySearch(t_phone* phone, int search, int number)
{
	int left = 0;
	int right = number - 1;
	int mid;

	while (left <= right)
	{
		mid = left + (right - left) / 2;

		if (phone[mid].stock == search)
		{
			return phone[mid].price;
		}
		if (phone[mid].stock < search)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int main(void)
{

	FILE* fp = fopen("phone.txt", "r");

	if (fp == NULL)
		printf("Very very masallah");
	else
	{
		int number;
		int search;
		int result;

		fscanf(fp, "%d", &number);

		t_phone* phone = (t_phone*)malloc(sizeof(t_phone) * number);
		readFile(fp, phone, number);
		display(phone, number);

		do {
			printf("Enter a number of stocks to see campaign: ");
			scanf("%d", search);


			if (search != -1)
			{






			}


		} while (search != -1);
	}










	return 0;
}