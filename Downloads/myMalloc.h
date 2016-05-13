#ifndef MYMALLOC_H
#define MYMALLOC_H

   /*	NOTES:
	*	this is a doubly linked list 
	*	allocation of blocks runs in LINEAR time
		to the blocks already created
	*	freeing of blocks is done in CONSTANT time 
		since it is DOUBLY LINKED 
		(is singly-linked then it would be LINEAR)
	*/

struct memEntry {
	struct memEntry *prev, *succ;
	int isFree; // is it free or is it allocated?
	int size; //number of free bytes
};

typedef struct memEntry memEntry;

#endif