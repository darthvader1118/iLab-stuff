/*
 * sorted-list.c
 */

#include <string.h>
#include "sorted-list.h"
#include "sorted-list.c"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}


//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}


int main()
{
	int i;
	//int intTest[10] = {3,8,80,34,68,10,20,1,0,-6};
	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	int *c = malloc(sizeof(int));
	int *d = malloc(sizeof(int));
	int *e = malloc(sizeof(int));
	*a = 3;
	*b = 8;
	*c = 80;
	*d = 64;
	*e = 34;
	int *intest[5] = {a,b,c,d,e};
	CompareFuncT comp = &compareInts;
	DestructFuncT dest = &destroyBasicTypeAlloc;
	SortedListPtr test = SLCreate(comp,dest);
	for(i = 0; i < (sizeof(intest)/sizeof(intest[0]));i++){
		SLInsert(test,(void*)intest[i]);
	}
	/*
	 *	*(int*)ptr->value
	 */
	SortedListIteratorPtr it = SLCreateIterator(test);
	for(i = 0; i<(sizeof(intest)/sizeof(intest[0]))-1;i++){
		printf("%d\n",*(int *)SLNextItem(it));
	}
	
	for(i = 0; i<(sizeof(intest)/sizeof(intest[0]));i++){
		SLRemove(test, (void*)intest[i]);
	}

return 0;
}
