//
// Circular Queue Implementation, CTIS 152
//
#define QUEUE_SIZE  100
#define STR_SIZE  20

typedef struct 
{
	char plate[STR_SIZE];
	char fuel;
	double liter;
	double payment;
} cust_t;

typedef  cust_t  QType;

QType  QUEUE_EMPTY = { "",'.',0.0,0.0 };

typedef struct _Queue
{
	int front, rear;
	QType data[QUEUE_SIZE];
	int counter;
} queue_t;

//Functions in this file...
void initializeQ(queue_t* q);
int isEmptyQ(queue_t* q);
int isFullQ(queue_t* q);
void insert(queue_t* q, QType item);
QType remove(queue_t* q);

//------------------------------------------------------------------------------

void initializeQ(queue_t* q)
{
	q->front = 0;
	q->rear = -1;
	q->counter = 0;
}

//------------------------------------------------------------------------------

int isEmptyQ(queue_t* q)
{
	if (q->counter == 0)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------

int isFullQ(queue_t* q)
{
	if (q->counter == QUEUE_SIZE)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------

void insert(queue_t* q, QType item)
{
	if (isFullQ(q))
		printf("Error: Queue is full!\n");
	else
	{
		q->rear = (q->rear + 1) % QUEUE_SIZE;   // make it circular
		q->data[q->rear] = item;
		(q->counter)++;
	}
}

//------------------------------------------------------------------------------

QType remove(queue_t* q)
{
	QType item;
	if (isEmptyQ(q))
	{
		printf("Error: Queue is empty!\n");
		item = QUEUE_EMPTY;
	}
	else
	{
		item = q->data[q->front];
		q->front = (q->front + 1) % QUEUE_SIZE;
		(q->counter)--;
	}
	return item;
}
/*
//
// Adjusted circular queue algorithm for a specific quesiton
//
#define QUEUE_SIZE  7
#define STR_SIZE 30

typedef  char  QType;

QType  QUEUE_EMPTY[STR_SIZE] = ""; //this is to return a value if there is no value.

typedef struct{
	int front, rear;
	double liter[QUEUE_SIZE];
	char fuel[QUEUE_SIZE];
	double price[QUEUE_SIZE];
	QType plate[QUEUE_SIZE][STR_SIZE];
	int counter;
} queue_t;

//------------------------------------------------------------------------------

void initializeQ(queue_t* q)
{
	q->front = 0;
	q->rear = -1;
	q->counter = 0;
}

//------------------------------------------------------------------------------

int isEmptyQ(queue_t* q)
{
	if (q->counter == 0)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------

int isFullQ(queue_t* q)
{
	if (q->counter >= QUEUE_SIZE)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------

void insert(queue_t* q, char* plate, char fuel, int liter, double price)
{
	if (isFullQ(q))
		printf("Error: Queue is full!\n");
	else
	{
		q->rear = (q->rear + 1) % QUEUE_SIZE;   // make it circular !!!!!!!
		strcpy(q->plate[q->rear], plate);
		q->fuel[q->rear] = fuel;
		q->liter[q->rear] = liter;
		q->price[q->rear] = price;
		q->counter++;
	}
}

//------------------------------------------------------------------------------

QType* remove(queue_t* q)
{
	QType item[STR_SIZE];
	if (isEmptyQ(q))
	{
		printf("Error: Queue is empty!\n");
		strcpy(item, QUEUE_EMPTY);		//that the answer of why we made an initialization at the beginning.
	}
	else
	{
		strcpy(item, q->plate[q->front]);
		q->front = (q->front + 1) % QUEUE_SIZE; //again, to make it circular
		(q->counter)--;
	}
	return item;
}*/