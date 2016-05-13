#include "sorted-list.h"
#include <stdio.h>
#include <string.h>
/*
 * big-O analysis
 *
 *
 *
 */
Node *createNode(void *newObj){
	Node *pd = (Node *)malloc(sizeof(Node));
	pd->data = newObj;
	pd->refCount = 0;
	pd->next = NULL;
	return pd;
}
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
	 SortedListPtr thing;
	thing = (SortedListPtr)malloc(sizeof(struct SortedList));

	//seting the values to DestructFuncT and CompareFuncT
	thing->DestructFuncT = df;
	thing->CompareFuncT = cf;

	return thing;
}
void SLDestroy(SortedListPtr list){

	//check if there is anythign in the list
	if(!list){
		return;
	}

	//destroy the nodes

	Node *pointer = (Node *)malloc(sizeof(Node));

	while(list->head != NULL){

		list->DestructFuncT(list->head->data);
		pointer = list->head;
		list->head = list->head->next;
		// and free the nodes.
		free(pointer);
	}
	free(list);
}
int checkinsert(SortedListPtr list, void *newObj)
{

	if (list==NULL || newObj==NULL)
	{

		return -1;
	}
	if (list!=NULL && newObj!=NULL)
	{

		return 1;
	}

}




int SLInsert(SortedListPtr list, void *newObj)
{

	Node *prev= (Node *)malloc(sizeof(Node));
	Node *ptr = (Node *)malloc(sizeof(Node));
	Node *newNode = createNode(newObj);
	// check if there is anything in the list
	int y = checkinsert(list,newObj);
	if (y==-1)
	{

		return 0;

	}	

	else if (y==1){



	//now there is something in the list or newobj
	//we have to create a new node

	Node *tmpNode = createNode(newObj);

	if(list->head == NULL || list->CompareFuncT(list->head->data, newObj) < 0){
		//the tempnode should point to the live head
		tmpNode->next = list->head;
		//the head should be the tempnode
		list->head = tmpNode;
		list->head->refCount++;

		return 1;
	}	


	ptr = list->head;
	while(ptr!=NULL){
	// make sure there is no same thing inserted twice
		if(list->CompareFuncT(ptr->data, newObj) == 0){
			return 0;
		}
	//if the new node is bigger then insert tht
		else if(list->CompareFuncT(ptr->data, newObj) < 0){
			// insert that new node
		if(prev == NULL){
			//check if that is bigger and if it then make changes to the head.
			Node *temp = ptr;
			list->head = newNode;
			//make the old head as the next of the head.
			newNode->next = temp;
		}
		prev->next = newNode;
		newNode->next = ptr;
		newNode->refCount++;
		return 1;
	}
	//this is if the new object is smaller then continue on
	else if(list->CompareFuncT > 0){
		prev = ptr;
		ptr = ptr->next;
		}
	}
	prev->next = newNode;
	return 1;
	}
	free(prev);
}
int SLRemove(SortedListPtr list, void *newObj)
{
	if(!list ){
		return 0;
	}
	if(list->head){
		return 0;
	}
	if(!newObj){
		return 0;
	}



	Node *ptr = list->head;

	Node *prev = (Node *)malloc(sizeof(Node));
	prev = NULL;
	while(ptr != NULL){
		if(list->CompareFuncT(ptr->data, newObj) == 0){
			if(prev == NULL){

				//delete the head of the list
			       list->DestructFuncT(newObj);
			       prev = list->head;
			       list->head = list->head->next;
			/*if(list->head){
				//the current node
				list->head->refCount++;
			}
			*/
			ptr->refCount--;
			//if there is nothing pointing to this node put the data
			if(ptr->refCount == 0){
				list->DestructFuncT(ptr->data);
				if(ptr->next !=NULL){
					//ptr has next , decrement the refcount
					ptr->next->refCount--;
				}	
				free(ptr);
				return 1;
			}
			}
			else{

			prev->next = ptr->next;
			//if the node has a next, we would increment the refcount
			if(ptr->next != NULL){
				ptr->next->refCount++;
				ptr->refCount--;
			}
			if(ptr->refCount <=0){
				list->DestructFuncT(ptr->data);
				if(ptr->next != NULL){
					ptr->next->refCount--;
				}
			free(ptr);
			return 1;
			}
		}
	}
	prev = ptr;
	ptr = ptr->next;
	}
	return 0;
}
SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
	SortedListIteratorPtr iter = (SortedListIteratorPtr)malloc(sizeof(struct SortedListIterator));
	iter->ptr = list->head;
	iter->prev = list->head;
	iter->ptr->refCount++;
	if(list->head == NULL)
		return NULL;
	else{
		return iter;
	}
}



void SLDestroyIterator(SortedListIteratorPtr iter){
	free(iter->ptr);
	free(iter);
}


void * SLGetItem( SortedListIteratorPtr iter ){
	if(iter->ptr == NULL){
		return 0;
	}
	else{
		return iter->ptr->data;
	}
}

/*
 * SLNextItem returns the next object in the list encapsulated by the
 * given iterator.  It should return a NULL when the end of the list
 * has been reached.
 *
 * One complication you MUST consider/address is what happens if a
 * sorted list encapsulated within an iterator is modified while that
 * iterator is active.  For example, what if an iterator is "pointing"
 * to some object in the list as the next one to be returned but that
 * object is removed from the list using SLRemove() before SLNextItem()
 * is called.
 *
 * You need to fill in this function as part of your implementation.
 */

void * SLNextItem(SortedListIteratorPtr iter){
	//check if the iterator is pointing nowhere
	if(iter->ptr == NULL){
		return NULL;
	}
	//check if the next node the iterator is pointing to is null
	else if(iter->ptr->next == NULL){
		
		iter->ptr->refCount--;
		//deleting node if refcount == 0
		if(iter->ptr->refCount == 0){
			free(iter->ptr);
			iter->ptr == NULL;
			return iter->ptr;
		}
		return NULL;
	}
	else{
		iter->ptr->refCount--;
	
		//deleting node if refcount == 0
		if(iter->ptr->refCount == 0){
			free(iter->ptr);
			iter->prev->next= iter->ptr;
			iter->ptr = iter->ptr->next;
			return iter->ptr->data;
		}
		//if all other conditions are not satisfied
		iter->prev = iter->ptr;
		iter->ptr = iter->ptr->next;
		iter->ptr->refCount++;
		return iter->ptr->data;
	}
	}
