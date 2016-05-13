#ifndef category_h
#define category_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>


//Each node corresponds to an order
struct Node_{
	char *title;
	char *price;
	char *ID;
	char *category;
	float remainingBalance;
	struct Node_ *next;
};
typedef struct Node_ Node;

//Orders are organized in a queue structure
struct Queue_{
	int size;
	Node *front;
	Node *back;
};
typedef struct Queue_ Queue;

//customer structure 
struct Customer_{
    char *name;
    char *ID;
    float balance;
    char *address;
    char *state;
    char *zip;
    Queue *purchasedList; //list of sucessfully purchased books
    Queue *rejectedList; //list of unsucessfully purchased books
};
typedef struct Customer_ Customer;


//FILES for database and Orders args
FILE *database, *order, *cat;
//array of customers
Customer **customerList;


//mutex lock for threads
pthread_mutex_t lock;
//pthread_t array index
int threadIndex;
float totalRevenue;

//thread_functions.c Functions
char *Concat(char *string, char letter);
Customer **getCustomers(FILE *database);
int getIndex(char *ID);
int numCat(char *categories);
void *processCategory(void *category);
void output(Customer **customerList);
void freeCustomers(Customer **customerList);
char *getCategories(FILE *cat);


//Global variables
Queue *queue;

//Functions of queues
Queue *createQueue();

Queue *fillQueue(FILE *order);

Queue *insertToQueue(Customer *customer, Node *newNode, bool successful);

void deQueue(Queue *queue);


#endif
