/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Allen Chan
 * Email: chanall@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */

struct pq_node{
  int priority;
  void* value;
};

struct pq{
  struct dynarray* array;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
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
  int size = dynarray_size(pq->array);
  
  if(size == 0){
    return 1;
  }
  else{
    return 0;
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
void pq_insert(struct pq* pq, void* value, int priority) {
  struct pq_node* new_node = malloc(sizeof(struct pq_node));
  new_node->value = value;
  new_node->priority = priority;
  
  printf("value = %d", new_node->priority);
  dynarray_insert(pq->array, new_node);

  struct pq_node* temp;
  int node_idx = dynarray_size(pq->array) - 1;
  int parent = 0;

  while(parent >= 0){
    parent = (node_idx - 1) / 2;
    temp = (struct pq_node*)dynarray_get(pq->array, parent);

    if(new_node->priority < temp->priority){
      dynarray_set(pq->array, parent, new_node);
      dynarray_set(pq->array, node_idx, temp);
      node_idx = parent;
    }
    else{
      break;
    }
  }

  temp = NULL;

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
  struct pq_node* front = (struct pq_node*)dynarray_get(pq->array, 0);

  if(front == NULL){
    return NULL;
  }
  else{
    return front->value;
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
 struct pq_node* front = (struct pq_node*)dynarray_get(pq->array, 0);

  return front->priority;
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
  int size = dynarray_size(pq->array) - 1;

  struct pq_node* first = (struct pq_node*)dynarray_get(pq->array, 0);
  struct pq_node* last = (struct pq_node*)dynarray_get(pq->array, size);

   dynarray_set(pq->array, 0, last);
   dynarray_remove(pq->array, size);
   
   last = NULL;
   int node = NULL;
   int lchild = NULL; 
   int rchild = NULL;
   int mchild = NULL;
   int loop = NULL;
  
   struct pq_node* temp;
   struct pq_node* temp2;

   while(loop == 0){
    lchild = (2 * node) + 1;
    rchild = (2 * node) + 2;
  
    if(lchild > dynarray_size(pq->array) - 1){
      break;
    }
    else if(lchild == dynarray_size(pq->array) - 1){
      mchild = lchild;
    }
    else{
      if(((struct pq_node*)dynarray_get(pq->array, lchild))->priority < ((struct pq_node*)dynarray_get(pq->array, rchild))->priority){
        mchild = lchild;
      }
      else{
        mchild = rchild;
      }
    }
    //printf("MIN CHILD = %d", mchild);

    if((((struct pq_node*)dynarray_get(pq->array, node))->priority) > (((struct pq_node*)dynarray_get(pq->array, mchild))->priority)){
      temp = (struct pq_node*)dynarray_get(pq->array, mchild);
      temp2 = (struct pq_node*)dynarray_get(pq->array, node);

      dynarray_set(pq->array, mchild, temp2);
      dynarray_set(pq->array, node, temp);  

      node = mchild;
    }
    else{
      break;
    }

   }
  
if(first != NULL){
  void* value = first->value;
  free(first);
  return value;
}
else{
  return NULL;
}


  //return NULL;
}
