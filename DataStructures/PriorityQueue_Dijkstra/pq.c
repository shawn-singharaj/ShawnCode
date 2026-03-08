/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Shawn Singharaj
 * Email: singhars@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>


#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* array;
};

/*
	This structure represents an individual element in the prioirty queue.
	It contains the value and the priority used to order the queue. 
*/
struct element{
	void* value;
	int priority;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* new_pq = (struct pq*) malloc(sizeof(struct pq)); // allocate memory for priority queue
	new_pq->array = dynarray_create();							// allocate memory for dynamic array

	return new_pq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	
	dynarray_free(pq->array);	// free array then queue
	free(pq);

	return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	
	return dynarray_size(pq->array) == 0;	// returns 1 if empty
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	
	struct element* new_element = (struct element*) malloc(sizeof(struct element));	// new element to be inserted allocated
	new_element->value = value;
	new_element->priority = priority;

	// insert element into end of array
	dynarray_insert(pq->array, new_element);		

	// set i to last index
	int i = dynarray_size(pq->array) - 1;

	// sort upwards
	while((i > 0) ){
		int parent_idx = (i - 1) / 2; // parent index

		struct element* current_element = dynarray_get(pq->array, i);
		struct element* parent_element = dynarray_get(pq->array, parent_idx);

		if(current_element->priority < parent_element->priority){	// if the current element's priority is smaller than its parent, then swap
			dynarray_set(pq->array, i, parent_element);
			dynarray_set(pq->array, parent_idx, current_element);
			i = parent_idx;
		}
		else{ // if largerm then break
			break;
		}
	}

	return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	
	// return first element's value
	struct element* element = dynarray_get(pq->array, 0);
	return element->value;									
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	
	// return first element's priority
	struct element* element = dynarray_get(pq->array, 0);
	return element->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	
	// get the first element and save its value to be returned
	struct element* first_element = dynarray_get(pq->array, 0);
	void* removed_value = first_element->value;

	// get last element to be swapped with first
	int last_idx = dynarray_size(pq->array) - 1;
	struct element* last_element = dynarray_get(pq->array, last_idx);

	// set the first index to the last element, remove last index to size down
	dynarray_set(pq->array, 0, last_element);
	dynarray_remove(pq->array, last_idx);
	
	free(first_element); // free the first element
	
	int i = 0;

	// sort downwards
	while((i < dynarray_size(pq->array)) ){
		int left_child = i * 2 + 1;		// find children indexes
		int right_child = i * 2 + 2;
		int small_idx = i;				// smallest index set to current index

		struct element* small_element = dynarray_get(pq->array, i); // get the element of smallest index

		if(left_child < dynarray_size(pq->array)){
			struct element* left_element = dynarray_get(pq->array, left_child); // find left child element
			if(small_element->priority > left_element->priority){				// if larger than parent, swap indexes
				small_idx = left_child;
			}
		}
			
		if(right_child < dynarray_size(pq->array)){										
			struct element* right_element = dynarray_get(pq->array, right_child);	// find right child element
			struct element* smallest_element = dynarray_get(pq->array, small_idx);	// in case smallest index is updated
			if(smallest_element->priority > right_element->priority){				// if larger than parent, swap indexes
				small_idx = right_child;
			}
		}

		if(small_idx == i){	// if nothing changes, break
			break;
		}

		struct element* temp = dynarray_get(pq->array, small_idx);	// swap smallest element at smallest index with current
		dynarray_set(pq->array, i, temp);
		dynarray_set(pq->array, small_idx, small_element);

		// increment
		i = small_idx;	
	}
	  
	return removed_value;
}

