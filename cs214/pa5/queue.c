
#include "category.h"

//Creates a queue with size, front, & back parameters equal to 0, null, null
Queue *createQueue(){
	Queue *newQueue = (Queue*)malloc(sizeof(Queue));
	newQueue->size = 0;
	newQueue->front = NULL;
	newQueue->back = NULL;
	return newQueue;
}

//Fills a queue with the orders from file
Queue *fillQueue(FILE *order){
	char s = getc(order);
	char *string = (char*)malloc(sizeof(char));
	string = "";
	
	//Create a string from file
	while(s != EOF){
		string = Concat(string, s);
		s = getc(order);
	}
	
	Queue *newQueue = createQueue();
	
	//Tokenize the string, create a node for each order, and add the node to queue
	char *tk, *placehold, *delims;
	placehold = NULL;
	delims = "|\n";
	tk = strtok_r(string, delims, &placehold);
	while(tk != NULL){
		Node *newNode = (Node*)malloc(sizeof(Node));
		newNode->title = tk;
		tk = strtok_r(NULL, delims, &placehold);
		newNode->price = tk;
		tk = strtok_r(NULL, delims, &placehold);
		newNode->ID = tk;
		tk = strtok_r(NULL, delims, &placehold);
		newNode->category = tk;
		tk = strtok_r(NULL, delims, &placehold);
		newNode->remainingBalance = 0;
		newNode->next = NULL;
		if(newQueue->front == NULL){
			newQueue->size++;
			newQueue->front = newNode;
			newQueue->back = newNode;
		}else{
			newQueue->size++;
			newQueue->back->next = newNode;
			newQueue->back = newNode;
		}
	}
	return newQueue;
}

//Inserts an order node to queue for the customer in successful(T) or unsuccessful(F) order list
Queue *insertToQueue(Customer *customer, Node *newNode, bool successful){
	if(successful){ //Add to successful order list
	if(customer->purchasedList->front == NULL){ //Create new successful order list if it does not already exist
			customer->purchasedList->front = newNode;
			customer->purchasedList->back = newNode;
		}else{ //Add to present successful order list if it already exists
			customer->purchasedList->back->next = newNode;
			customer->purchasedList->back = newNode;
		}
		customer->purchasedList->size++;
		return customer->purchasedList;
	}else{ //Add to unsuccessful order list
		if(customer->rejectedList->front == NULL){ //Create new unsuccessful order list if it does not already exist
			customer->rejectedList->front = newNode;
			customer->rejectedList->back = newNode;
		}else{ //Add to present unsuccessful order list if it already exists
			customer->rejectedList->back->next = newNode;
			customer->rejectedList->back = newNode;
		}
		customer->rejectedList->size++;
		return customer->rejectedList;
	}
}

//deQueues all nodes in a given queue
void deQueue(Queue *queue){
	int qsize = queue->size;
	int i;
	Node *prev, *curr;
	prev = NULL;
	curr = queue->front;
	for(i = 0; i < qsize; i++){
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	return;
}
