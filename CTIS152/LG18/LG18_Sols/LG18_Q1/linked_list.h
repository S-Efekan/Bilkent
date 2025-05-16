#pragma once

typedef int LType;

typedef struct node_s {
	LType data;
	struct node_s* next;
}node_t;

node_t* getnode ( ) {
	node_t* newp;
	newp = (node_t*)malloc ( sizeof ( node_t ) );
	newp->next = NULL;
	return(newp);
}

void addAfter ( node_t* p, LType item ) {
	node_t* np;
	np = getnode ( );
	np->data = item;
	np->next = p->next;
	p->next = np;
}

node_t* addBeginning ( node_t* hp, LType item ) {
	node_t* np;
	np = getnode ( );
	np->data = item;
	np->next = hp;
	return hp;
}