/*
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 *
 * Ashley Song, CS50, 19X, Lab3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "memory.h"



/**************** local types ****************/
typedef struct counterNode {
  int theKey;                // pointer to data for this item
  struct counterNode *next;       // link to next node
  int count;
} counterNode_t;

/**************** global types ****************/
typedef struct counters {
  struct counterNode *head;
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see bag.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static counterNode_t *counterNode_new(int key);


/**************** counters_new ****************/
/* Create a new (empty) counter structure.
 *
 * We return:
 *   pointer to a new counterset; NULL if error.
 * We guarantee:
 *   counterset is intialized empty.
 * Caller is responsible for:
 *   later calling counters_delete();
 */
 counters_t *
 counters_new(void)
 {
   counters_t *counter = count_malloc(sizeof(counters_t));

   if (counter == NULL) {
     return NULL;              // error allocating bag
   } else {
     // initialize contents of bag structure
     counter->head = NULL;
     return counter;
   }
 }

/**************** counters_add ****************/
/* Increment the counter indicated by key.
 *
 * Caller provides:
 *   valid pointer to counterset, and key(must be >= 0)
 * We return:
 *   the new value of the counter related to the indicated key.
 *   0 on error (if ctrs is NULL or key is negative)
 * We guarantee:
 *   counter values will always be >= 1.
 * We do:
 *  ignore if ctrs is NULL or key is negative.
 *  if the key does not yet exist, create a counter for it and initialize to 1.
 *  if the key does exist, increment its counter by 1.
 */
int counters_add(counters_t *ctrs, const int key){
  if(key < 0 || ctrs == NULL){
    return 0;
  }

  for(counterNode_t *curr = ctrs->head; curr != NULL; curr = curr->next){   //if already in counterset, increment count and return count
    if((curr->theKey) == key){
      curr->count += 1;
      return curr->count;
    }
  }

  counterNode_t *new = counterNode_new(key);
  new->next = ctrs->head;  //add new node to the beginning of the counter list
  ctrs->head = new;  //set n
}

/**************** countNode_new ****************/
/* Allocate and initialize a countNode */
/* Not visible outside of this file */
/* Initialize count to 1 for each new node*/
static counterNode_t * // not visible outside this file
counterNode_new(int key){
  counterNode_t *node = count_malloc(sizeof(counterNode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->theKey = key;
    node->next = NULL;
    node->count = 1;
    return node;
  }
}


/**************** counters_get ****************/
/* Return current value of counter associated with the given key.
 *
 * Caller provides:
 *   valid pointer to counterset, and key(must be >= 0)
 * We return:
 *   current value of counter associte with the given key, if present,
 *   0 if ctrs is NULL or if key is not found.
 * Note:
 *   counterset is unchanged as a result of this call.
 */
int counters_get(counters_t *ctrs, const int key){
  if(key < 0 || ctrs == NULL){
    return 0;
  }

  for(counterNode_t *curr = ctrs->head; curr != NULL; curr = curr->next){     //iterate over to find the right node and return its count
    if((curr->theKey) == key){
      return curr->count;
    }
  }
  return 0;
}


/**************** counters_set ****************/
/* Set the current value of counter associated with the given key.
 *
 * Caller provides:
 *   valid pointer to counterset,
 *   key(must be >= 0),
 *   counter value(must be >= 0).
 * We return:
 *   false if ctrs is NULL, if key < 0 or count < 0, or if out of memory.
 *   otherwise returns true.
 * We do:
 *   If the key does not yet exist, create a counter for it and initialize to
 *   the given value.
 *   If the key does exist, update its counter value to the given value.
 */
bool counters_set(counters_t *ctrs, const int key, const int count){

  if(key < 0 || count < 0 || ctrs == NULL){
    return false;
  }

  for(counterNode_t *curr = ctrs->head; curr != NULL; curr = curr->next){   //iterate over to find the right node and update its count
    if((curr->theKey) == key){
      curr->count = count;
      return true;
    }
  }

  counterNode_t *new = counterNode_new(key);
  new->next = ctrs->head;
  ctrs->head = new;
  new->count = count;  //update
  return true;
}

/**************** counters_print ****************/
/* Print all counters; provide the output file.
 *
 * Caller provides:
 *   valid pointer to counterset,
 *   FILE open for writing.
 * We print:
 *   Nothing if NULL fp.
 *   "(null)" if NULL ctrs.
 *   otherwise, comma=separated list of key=counter pairs, all in {brackets}.
 */
void counters_print(counters_t *ctrs, FILE *fp){
  if(fp == NULL){
    return;
  }
  if(ctrs == NULL){
    fputc('{', fp);
    fputs("(null)", fp);
  }

  else{   //iterate over the nodes to print
    fputc('{', fp);
    for (counterNode_t *node = ctrs->head; node != NULL; node = node->next) {
      int nodeKey = node->theKey;
      int nodeCount = node->count;
      fprintf(fp, "%d=%d", nodeKey, nodeCount);
      fputc(',', fp);
    }
  }
  fputc('}', fp);

}


/**************** counters_iterate ****************/
/* Iterate over all counters in the set.
 *
 * Caller provides:
 *   valid pointer to counterset,
 *   arbitrary void*arg,
 *   valid pointer to itemfunc that can handle one item.
 * We do:
 *   nothing, if ctrs==NULL or itemfunc==NULL.
 *   otherwise, call itemfunc once for each item, with (arg, key, count).
 * Note:
 *   the order in which items are handled is undefined.
 *   the counterset is unchanged by this operation.
 */
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count)){
  if (ctrs != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (counterNode_t *node = ctrs->head; node != NULL; node = node->next) {
      int keyValue = node->theKey;
      int countValue = node->count;
      (*itemfunc)(arg, keyValue, countValue);
    }
  }
}

/**************** counters_delete ****************/
/* Delete the whole counterset.
 *
 * Caller provides:
 *   a valid pointer to counterset.
 * We do:
 *   we ignore NULL ctrs.
 *   we free all memory we allocate for this counterset.
 */
void counters_delete(counters_t *ctrs){
  counterNode_t *curr = ctrs->head;
  counterNode_t *next;
  while(curr != NULL) {
    next = curr->next;
    count_free(curr);
    curr = next;    //free each node 
  }
  count_free(ctrs);
  #ifdef MEMTEST
  count_report(stdout, "End of counters_delete");
  #endif
}

// #endif // __COUNTERS_H
