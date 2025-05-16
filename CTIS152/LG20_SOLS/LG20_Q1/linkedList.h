
typedef struct {
	char uname[10];
	char passwd[10];
}user_t;


typedef user_t LType;

typedef struct node_s
{	LType data;
	struct node_s *next; 
} node_t;

node_t *getnode ( ) 
{
	node_t *node;
	node = (node_t *) malloc (sizeof(node_t));
	node->next = NULL;
	return (node);
}

void addAfter (node_t *p, LType item)
{
	node_t *newp;
	newp = getnode();	
	newp->data = item;
	newp->next = p->next;
	p->next = newp;
}

node_t *addBeginning (node_t *headp, LType item)
{	
	node_t *newp;
	newp = getnode();	
	newp->data = item;
	newp->next = headp;
	return (newp);
}
// hp = addBeginning(*hp, item);


node_t* deleteFirst ( node_t* hp, LType* delItem )
{
	node_t* del;
	del = hp;
	*delItem = hp->data;
	hp = del->next;
	free ( del );
	return hp;
}			// Burada return head pointera gerçekleþir, LType call by reference ise düðüm silindikten sonra veriyi saklama isteðinden dolayý.


void deleteAfter( node_t prev, LType* delItem )
{
	node_t* del;
	del = prev.next;
	*delItem = del->data;
	prev.next = del->next;
	free ( del );
}