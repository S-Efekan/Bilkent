#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "linklist_int.h"

node_t*removeFromList ( node_t* hp, int item )
{
	while (hp->next != NULL && hp->next->data != item)
	{
		hp = hp->next;
	}
	if (hp->next != NULL)
	{
		deleteAfter ( hp );
	}
	return hp;
}


void displayRec (node_t*p )
{
	if (p->next != NULL)
		displayRec ( p->next );

	printf ( "%d <- ", p->data );
}

int main ( )
{
	node_t* hp = getnode();
	node_t* p = getnode();

	int number = 0;

	while (number != -1)
	{
		printf ( "Enter a number (-1 to exit): " );
		scanf ( "%d", &number );

		if (number != -1)
		{
			hp = addBeginning ( hp, number );
		}
	}

	int rmv;

	printf ( "Enter a number to remove from list: " );
	scanf ( " %d", &rmv );

	p = removeFromList ( hp, number );

	if (p->next != NULL)
		printf ( "\n<%d> removed from list.", p->data );
	else
		printf ( "\nThere is no such a number!" );


	printf ( "NULL <- " );
	displayRec ( hp );











	return 0;
}