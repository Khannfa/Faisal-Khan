/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Khanfa
 * Email: Khanfa@oregonstate.edu
 */

#include <stdlib.h>
#include "dynarray.h"
#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray *array;

};
	struct pq_elem{

	int prior;
	void* data;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* pq = malloc(sizeof( struct pq*));
	pq->array = dynarray_create();


	return pq;
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
	dynarray_free(pq->array);
	free(pq);

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


	if(dynarray_size(pq->array) != 0){
		int size = dynarray_size(pq->array);
		return 0;
	}
	else if (dynarray_size(pq->array) == 0){
		int size_2 = dynarray_size(pq->array);
		return 1;
	}
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
void pq_insert(struct pq* pq, void* data, int priority) {
	struct pq_elem* e = malloc(sizeof(struct pq_elem));
	struct pq_elem* node_parent = malloc(sizeof(struct pq_elem)); 

	if(dynarray_size(pq->array) == 0)
	{ 
		e->data = data;
		e->prior = priority;
		dynarray_insert(pq->array,-1,e); 
	}
	else
	{ 
		e->data = data;
		e->prior = priority; 
		dynarray_insert(pq->array,-1,e);

		int indx = dynarray_size(pq->array) - 1; 
		int done = 0;
		while(!done)
		{ 
			node_parent = dynarray_get(pq->array,(indx - 1) / 2);
			if(node_parent->prior > e->prior && indx > 0)
			{ 
				dynarray_set(pq->array,(indx - 1) / 2, e);
				dynarray_set(pq->array,indx,node_parent);
				indx = (indx - 1) / 2; 
			}
			else
			{ 
				done = 1;
			}

		}
	}
//free(e);
//free(node_parent);	
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
  	if(dynarray_size(pq->array)==0){

		return NULL;
	}
	else{
		return ((struct pq_elem*)dynarray_get(pq->array,0))->data;

	}
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
  	struct pq_elem* e = malloc(sizeof(struct pq_elem));

	e = dynarray_get(pq->array, 0);
	return e->prior;
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
	struct pq_elem* e = NULL;
	struct pq_elem* r = NULL;
	struct pq_elem* lc = NULL;//leftchild
	struct pq_elem* rc =NULL;//rightchild
	int lci, rci;
	r = dynarray_get(pq->array, 0);
	if (dynarray_size(pq->array) == 1)
	{
		dynarray_remove(pq->array,-1);
		return r->data;
	}
	dynarray_set(pq->array,0,dynarray_get(pq->array,-1));

	dynarray_remove(pq->array,-1); 

	int done = 0;
	int indx = 0;
	// can I group these as one percolation function?
	while(!done)
	{
		lci = (indx * 2) + 1;//leftchildindex 
		rci = (indx * 2) + 2;//rightchildindex


		e = dynarray_get(pq->array, indx);

		if(rci<dynarray_size(pq->array)&&lci<dynarray_size(pq->array)){


			lc = dynarray_get(pq->array,lci);

			rc = dynarray_get(pq->array,rci);

			if(rc->prior >= lc->prior){		

				if(e->prior> lc->prior){

					dynarray_set(pq->array, lci, dynarray_get(pq->array, indx));

					dynarray_set(pq->array, indx, lc);

					indx = lci;				

				}	
				else{
					done = 1;
				}

			}
			else{


				if(e->prior>rc->prior){

					dynarray_set(pq->array, rci, dynarray_get(pq->array, indx));

					dynarray_set(pq->array, indx, rc);

					indx = rci;
				}

				else{
					done = 1;
				}

			}
		}
		else if(lci<dynarray_size(pq->array)){
			
			lc = dynarray_get(pq->array,lci);
			done =1;

			if(lc->prior<e->prior){		


				dynarray_set(pq->array, lci, dynarray_get(pq->array, indx));

				dynarray_set(pq->array, indx, lc);

			}
		}

		else{
			done =1;
		}
	}

	return r->data;

}

