#include "category.h"

static pthread_t *tids;

char *Concat(char *string, char letter){ //concatenate a char to end of a string
	char *str = string;
	char let = letter;
	size_t len = strlen(str);
	char *result = (char*) malloc((len + 2) * sizeof(char));
	strcpy(result, str);
	result[len] = let;
	return result;
}

int main(int argc, char** argv){
	totalRevenue = 0;
	database = fopen(argv[1], "r"); order = fopen(argv[2], "r"); cat = fopen(argv[3], "r");
	if(database == NULL || order == NULL || cat == NULL){ 
		puts(" Error opening files "); //error message if given an empty file  
		return 1;
	}

	if(pthread_mutex_init(&lock, NULL) != 0){ //initialize mutex lock
		puts(" Mutex init failed ");
	}

	customerList = getCustomers(database); 
	if(customerList == NULL){ 
		puts(" Error making database "); // if database doesn't exist 
		return 1;
	}
	queue = createQueue();
	queue = fillQueue(order); //fill queue with order file data
	int i;
	char *categories = (char*) getCategories(cat);
	tids = (pthread_t*)malloc(numCat(categories)*sizeof(pthread_t)); //initialize pthread array for each category
	threadIndex = 0; 
	int strIndex = 0; 
	char *string =(char *)malloc(sizeof(char));
	string = "";
	char c;
	
	do{ //create thread for each unique category
		c = categories[strIndex];
		if(c == ' ' || c == '\0'){ // new category, create a thread
			if(pthread_create(&tids[threadIndex], NULL, processCategory, (void*)string) != 0){ //create thread passing category function
				puts(" Error making new thread ");
				return 1;
			}
			threadIndex++;
			string = "";
		}else{ //not a new category,just add to string
			string = Concat(string, c);
		}
		strIndex++;
	}while(c != '\0');
	
	for(i=0; i<numCat(categories); i++){ // join all the category threads and wait until finished
		pthread_join(tids[i],NULL);
	}
	
	output(customerList); 
	
	//free and close everything
	freeCustomers(customerList);
	deQueue(queue);
	free(tids);
	fclose(database);
	fclose(order);
	fclose(cat);
	return 0;
}
