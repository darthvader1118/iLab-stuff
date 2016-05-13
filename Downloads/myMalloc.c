#include <stdlib.h>
#include <stdio.c>
#include "myMalloc.h"

#define MESIZE sizeof(struct memEntry)
#define BLOCKSIZE (1024*1024)

static char big_block[BLOCKSIZE];

void* myMalloc(unsigned int size){
	static int initialized = 0;
	static memEntry *root;
	memEntry *p, *succ;

	if(!initialized){
		root = (memEntry*) big_block;
		root->prev = root->succ = 0;
		root->size = BLOCKSIZE - MESIZE;
		root->isFree = 1; 
		initialized = 1;
	}

	p=root;

	do{
		if(p->size < size) //the block is too small
			p = p->size;
		else if(!p->isFree) // is the block allocated?
			p=p->succ;
		else if(p->size < (size + MESIZE)){ // is it too small to chop up?
			p->isFree = 0;
			return (char*) p + MESIZE; //room for more!
		}
		else{
			succ = (memEntry*)((char*) p + MESIZE + size);
			succ->succ = p->succ;
			if(p->succ != 0)
				p->succ->prev = succ;
			p->succ = succ;
			succ->size = p->size - MESIZE - size;
			succ->isFree = 1;
			p->size = size;
		}

	} while(p!=0);
	return 0;
}

void myFree(void *p){
	memEntry *ptr, * pred, *succ;
	ptr = (memEntry*) ((char*)p - MESIZE);
	if(((pred = ptr->prev) != 0) && pred->isFree){
		pred->size += MESIZE + ptr->size;
		pred->succ = ptr->succ;
		if(ptr->succ != 0)
			ptr->succ->prev = pred;
	} else {
		ptr->isFree =1;
		pred = ptr;
	}
	if(((succ=ptr->succ) != 0) && succ->isFree){
		pred->size += MESIZE;
		pred->succ = succ->succ;
		if(succ->succ != 0)
			succ->succ->prev = pred;
	}
}
