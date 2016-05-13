
#include "book_order.h"

//function creates customer array database
customer **getCustomers(FILE *database){
        char c;
        char *string = (char*)malloc(sizeof(char));
        string = "";
    c = getc(database);
    while(c != EOF){  //turn file into string
            
        string = Concat(string, c);
        c = getc(database);
    }
    if(strlen(string) == 0){

        return NULL;
    }    
        customer **customerList = (customer**)malloc(200*sizeof(customer*));

        char *token, *hold, *seps;
        hold = NULL;
        seps = "|\n";
        token = strtok_r(string, seps, &hold);
        while(token != NULL){ // tokenize string into individual customers

                customer *new = (customer*)malloc(sizeof(customer));
                new->name = token;
                token = strtok_r(NULL, seps, &hold);
                new->ID = token;
                token = strtok_r(NULL, seps, &hold);
                new->balance = atoi(token);
                token = strtok_r(NULL, seps, &hold);
                new->address = token;
                token = strtok_r(NULL, seps, &hold);
                new->state = token;
                token = strtok_r(NULL, seps, &hold);
                new->zip = token;
                new->purchasedList = createQueue();
                new->rejectedList = createQueue();
                customerList[getIndex(new->ID)] = new;
                token = strtok_r(NULL, seps, &hold);
        }
        return customerList;
}

//function gets the index of the customer array from CustomerID
int getIndex(char *ID){

        return atoi(ID) % 200;
}

//funciton determines the number of categories from the categories argument string
int numCat(char *categories){

    int num = 0;
    int i;
    char c;
    for(i=0; i<strlen(categories); i++){ //loop through string

        c = categories[i];
        if(c == ' '){ //separator parse category
            num++;
        }
    }
    num++;
    return num;
}

//function that each thread calls, processing the orders for their individual category
void *processCategory(void *arg){
    pthread_mutex_lock(&lock); //lock mutex
    char* category = (char*)arg;
    customer *tempCustomer;
    Node *Order = queue->front;
    int queueSize = queue->size;
    int match;
    while(queueSize != 0){ //loop through order queue attaining each order matching the category 
                 
        match = strcmp(category, Order->category);
        if(match == 0){ //the order matches the thread category  
            tempCustomer = customerList[getIndex(Order->ID)]; //get customer
            if(tempCustomer->balance >= atof(Order->price)){ //customer has enough money to purchase order
               	tempCustomer->balance = tempCustomer->balance - atoi(Order->price);
               	Node *purchased = (Node*)malloc(sizeof(Node));
               	purchased->title = Order->title;
               	purchased->price = Order->price;
               	purchased->ID = Order->ID;
               	purchased->category = Order->category;
               	purchased->remainingBalance = tempCustomer->balance;
               	tempCustomer->purchasedList = insertToQueue(tempCustomer, purchased, 1);
               	totalRevenue += atof(Order->price);
               	printf("\nBook Purchase Successfull:\n\t%s|$%s|%s|%s|%s|%s\n", purchased->title, purchased->price, tempCustomer->name, tempCustomer->address, tempCustomer->state, tempCustomer->zip);
            }else{ //customer does not hace sufficient funds
              	Node *rejected = (Node*)malloc(sizeof(Node));
                rejected->title = Order->title;
               	rejected->price = Order->price;
               	rejected->ID = Order->ID;
               	rejected->category = Order->category;
               	rejected->remainingBalance = tempCustomer->balance;
             	tempCustomer->rejectedList = insertToQueue(tempCustomer, rejected, 2);
               	printf("\nRejected Order: \n\t%s|%s|$%s|%s\n", tempCustomer->name, Order->title, Order->price, Order->category);
            }

        }
    	Order = Order->next; //get next order
    	queueSize--;
    }
    pthread_mutex_unlock(&lock); //unlock mutex
    return NULL;
}

//function prints out the final report
void output(customer **customers){
    int i;
    int size;
    Node *ptr;
    for(i=0;i<200;i++){
        if(customers[i] != NULL){
            printf("=== BEGIN CUSTOMER INFO ===\n### BALANCE ###\n");
            printf("Customer name: %s\nCustomer ID: %s\nRemaining credit balance after all purchases (a dollar amount): $%.2f\n", customers[i]->name, customers[i]->ID, customers[i]->balance);
            printf("\n### SUCCESSFUL ORDERS ###\n");
            size = customers[i]->purchasedList->size;
            if(size > 0){
                ptr = customers[i]->purchasedList->front;
                while(size > 0){
                    printf("%s|$%s|$%.2f\n", ptr->title, ptr->price, ptr->remainingBalance);
                    ptr = ptr->next;
                    size--;
                }
            }
            printf("### REJECTED ORDERS ###\n");
            size = customers[i]->rejectedList->size;
            if(size > 0){
                ptr = customers[i]->rejectedList->front;
                while(size > 0){
                    printf("%s|$%s\n", ptr->title, ptr->price);
                    ptr = ptr->next;
                    size--;
                }
            }
            
            printf("=== END CUSTOMER INFO ===\n\n");
        }
    }
    printf("***Total Revenue: $%.2f***\n", totalRevenue);
    return;
}

//function frees all allocated customers
void freeCustomers(customer **customerList){

	int i;
	for(i=0; i<200; i++){

		if(customerList[i] != NULL){

			free(customerList[i]);
		}
	}
	return;
}
char *getCategories(FILE *cat){
	
        char c;
        char *string = (char*)malloc(sizeof(char));
        string = "";
    	c = getc(cat);
    	while(c != EOF){  //turn file into string
            
        	string = Concat(string, c);
        	c = getc(cat);
    	}
    	if(strlen(string) == 0){

        	return NULL;
    	}
        
	char *token, *hold, *seps, *final;
        hold = NULL;
	final = "";
        seps = " |\n";
        token = strtok_r(string, seps, &hold);
	strcat(final,token);
	while(token != NULL){
		strcat(final, " ");
		strcat(final, token);
		
		token = strtok_r(string, seps, &hold);

	}
	return strdup(final);


}





