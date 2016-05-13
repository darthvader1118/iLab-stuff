/*
 * sorted-list.c
 */

#include <string.h>
#include "sorted-list.h"
#include "sorted-list.c"

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
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
	char *a = malloc(6*sizeof(char));
	char *b = malloc(6*sizeof(char));
	char *c = malloc(3*sizeof(char));
	char *d = malloc(5*sizeof(char));
	char *e = malloc(8*sizeof(char));
	a = strcpy(a,"hello");
	b = strcpy(b,"world");
	c = strcpy(c,"my");
	d = strcpy(d,"name");
	e = strcpy(e,"Krishna");
	char *intest[5] = {a,b,c,d,e};
	CompareFuncT comp = &compareStrings;
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
		printf("%s\n",(char *)SLNextItem(it));
	}
	
	for(i = 0; i<(sizeof(intest)/sizeof(intest[0]));i++){
		SLRemove(test, (void*)intest[i]);
	}
	
	

return 0;
}
