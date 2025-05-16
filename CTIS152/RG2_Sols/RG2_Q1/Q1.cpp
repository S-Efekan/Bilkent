#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "queue_struct.h"

void fillQueue ( FILE* fp, queue_t* Q )
{
	QType item;
	while (fscanf ( fp, "%s %lf", item.shopName, &item.sale ) != EOF)
	{
		insert ( Q, item );
	}

}

void displayQueue ( queue_t Q )
{
	QType item;
	printf ( "The list of all Shops;\nShop Name        Sale Amount\n****************************\n" );
	while (!isEmptyQ ( &Q ))
	{
		item = remove ( &Q );
		printf ( "%-19s %.2f\n", item.shopName, item.sale );
	}

}

void shopOfTheDay ( queue_t Q )
{
	QType item;
	QType max;
	printf ( "\n" );

	item = remove ( &Q );
	max = item;
	while (!isEmptyQ ( &Q ))
	{
		item = remove ( &Q );

		if (item.sale > max.sale)
			max = item;
	}
	printf ( "The Shop Of The Day\n****************************\n" );
	printf ( "%-19s %.2f\n\n", max.shopName, max.sale );
}

void removeShop (queue_t*Q,char*shop )
{
	queue_t Q2; // To not affect original queue!
	Q2 = *Q;

	queue_t Qtemp;
	initializeQ ( &Qtemp );

	QType item;

	int found = 0;

	while (!isEmptyQ ( &Q2 ))
	{
		item = remove ( &Q2 );

		if (strcmp ( item.shopName, shop ) != 0)
		{
			insert ( &Qtemp, item );
		}
		else
			found = 1;
	}



	if (found)
	{
		
		*Q = Qtemp;
		printf ( "\n%s is deleted from shop list!\n", shop );
		displayQueue ( *Q );
		shopOfTheDay ( *Q );
	}
	else
	{
		printf ( "\nThere is no such a shop in the list!\n\n" );
	}
}


int main ( )
{
	FILE* fp = fopen("shops.txt","r");
	if (fp == NULL)
		printf ( "File error occured!" );
	else
	{
		queue_t Q;
		char shop[SIZE];

		initializeQ ( &Q );

		fillQueue ( fp, &Q );

		displayQueue ( Q );
		
		shopOfTheDay ( Q );

		printf ( "Which shop do you want to delete?: " );
		scanf ( " %[^\n]", shop );

		removeShop ( &Q, shop );

	}
	return 0;
}