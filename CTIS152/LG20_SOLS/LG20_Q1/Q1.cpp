#define _CRT_SECURE_NO_WARNINGS 1
#define HSIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
/***********************************************************************************************************************************/
int hashCode (char uname[10] )
{
	int total = 0;
	int i = 0;

	while (uname[i] != '\0')
	{
		total += uname[i];
		i++;
	}
	printf ( "Total of ascii codes: %d", total );
	return total % HSIZE;
}
/***********************************************************************************************************************************/
void initArray (node_t*A[] )
{
	int i;
	for (i = 0; i < HSIZE; i++)
	{
		A[i] = NULL;
	}
}
/***********************************************************************************************************************************/
int menu ( )
{
	int choice;
	{
		printf ( "\n\nMENU\n*************************************\n" );
		printf ( "1. Insert a supply into the Hash Table\n" );
		printf ( "2. Remove a supply from the Hash Table\n" );
		printf ( "3. Display a Hash Table\n" );
		printf ( "4. EXIT\n" );
	}

	printf ( "Please enter your choice: " );
	scanf_s ( " %d", &choice );
	return choice;
}
/***********************************************************************************************************************************/
node_t* searchUser (node_t*A,user_t user)
{
	while (A != NULL)
	{

	}



}
/***********************************************************************************************************************************/
void insertUser ( node_t* A[], LType item )
{
	int flag = 0;
	int index = hashCode ( item.uname );
	
	if (A[index] == NULL)
		A[index] = addBeginning ( A[index], item );
	else
	{
		node_t* B = A[index];

		while (B->next != NULL)
		{
			if (strcmp ( item.uname, B->data.uname ) == 0)
			{
				printf ( "\nThe user is already exists password updated!" );
				B->data = item;
				flag = 1;
				printf ( "\nInserted user : %s (username) | %s (password)\n", item.uname, item.passwd );
			}
			B = B->next;
		}
		if (flag == 0)
		{
			B = B->next;
			addAfter ( B, item );
		}
	}
}
/***********************************************************************************************************************************/
void display ( node_t* A[] )
{
	int i;
	node_t* B;
	for (i = 0; i < HSIZE; i++)
	{
		B = A[i];
		printf ( "\nHead [%d] ", i );
		if (B == NULL)
			printf ( "has no elements" );
		else
			printf ( "has elements : " );
		while (B != NULL)
		{
			printf ( "%s %s,", B->data.uname, B->data.passwd );
		}
		printf ( "\n" );
	}
}
/***********************************************************************************************************************************/
int main ( )
{
	int choice = 0;
	user_t temp_user;
	node_t*A[HSIZE];
	initArray ( A );
	do
	{
		do
		{
			choice = menu ( );
		} while (!(choice >= 1 && choice <= 4));

		if (choice != 4)
		{
			if (choice == 1)
			{
				printf ( "Enter a username and password: " );
				scanf ( " %s %s", &temp_user.uname, &temp_user.passwd );
				insertUser ( A, temp_user );
			}
			else if (choice == 2)
			{

			}
			else
			{
				display ( A );
			}

		}


	} while (choice != 4);
	return 0;
}