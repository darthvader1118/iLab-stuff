/*
 * sorted-list.c
 */

#include <string.h>
#include "sorted-list.h"
#include "sorted-list.c"
int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
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
	//int intTest[10] = {3.13,8,80,34,68,10,20,1,0,-6};
	double *a = malloc(sizeof(double));
	double *b = malloc(sizeof(double));
	double *c = malloc(sizeof(double));
	double *d = malloc(sizeof(double));
	double *e = malloc(sizeof(double));
	*a = 3.134;
	*b = 8.9034;
	*c = 80.434;
	*d = 64;
	*e = 34.343252;
	double *intest[5] = {a,b,c,d,e};
	CompareFuncT comp = &compareDoubles;
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
		printf("%e\n",*(double *)SLNextItem(it));
	}

	for(i = 0; i<(sizeof(intest)/sizeof(intest[0]));i++){
		SLRemove(test, (void*)intest[i]);
	}

	return 0;
}
