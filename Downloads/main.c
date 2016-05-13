#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myMalloc.h"

int main(int argc, char **argv){
	//Variables for error checking
	int x;
	char * p;
	
	//Check for first error condition: freeing unallocated memory
	free(&x);
	printf("The above should have returned an error.\n");
	
	//Check for second error condition: freeing memory not allocated by malloc
	p = (char *)malloc(200);
	free(p+10);
	printf("The above should have returned a second error.\n");
	
	//Check for third error condition: redundant freeing of the same pointer
	free(p);
	free(p);
	printf("The above should have returned a third error.\n");
	
	//The following should return no errors since the behavior is okay
	p = (char *)malloc(100);
	free(p);
	p = (char *)malloc(100);
	free(p);
	printf("The above should have returned no error.\n");
	
	//End main
	atexit(&LeakDetect);
	return 0;
}
