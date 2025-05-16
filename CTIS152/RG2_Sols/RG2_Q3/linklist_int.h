#pragma once


typedef struct node_b {
	int data;
	struct node_b* next;
}node_t;


node_t* getnode ( )
{
	node_t* node = (node_t*)malloc ( sizeof ( node_t ) * 1 );
	node->next = NULL;
	return node;
}


node_t* addBeginning ( node_t* hp, int item )
{
	node_t* node = getnode ( );
	node->data = item;
	node->next = hp;
	return node;
}

void addAfter ( node_t* p, int item )
{
	node_t* node;
	node = getnode ( );
	node->data = item;
	node->next = p->next;
	p->next = node;
}

node_t* deleteBeginning ( node_t* hp )
{
	node_t* node;
	node = hp->next;
	free ( hp );

	return node;
}

void deleteAfter ( node_t*p )
{
	node_t* temp;
	temp = p->next;
	p->next = p->next->next;
	free ( temp );
}