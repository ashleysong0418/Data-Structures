/*
 * hashtable.c - file for CS50 hashtable module
 *
 * A *hashtable* is a set of (key,item) pairs.  It acts just like a set,
 * but is far more efficient for large collections.
 *
 * Ashley Song, CS50, 19X, Lab3
 * Template from CS50
 */

// #ifndef __HASHTABLE_H
// #define __HASHTABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../set/set.h"
#include "jhash.h"
#include "memory.h"

/**************** global types ****************/
typedef struct hashtable{
  set_t **hashSlots;
  int slotSize;
} hashtable_t;

/**************** functions ****************/

/**************** hashtable_new ****************/
/* Create a new (empty) hashtable.
 *
 * Caller provides:
 *   number of slots to be used for the hashtable (must be > 0).
 * We return:
 *   pointer to the new hashtable; return NULL if error.
 * We guarantee:
 *   hashtable is initialized empty.
 * Caller is responsible for:
 *   later calling hashtable_delete.
 */
hashtable_t *hashtable_new(const int num_slots){
  //if(num_slots <= 0){
  //  return NULL;
  //}
  if (num_slots > 0){
    //allocating space for the hashtable
    hashtable_t *table = count_malloc(sizeof(hashtable_t));
    if(table == NULL){
      return NULL;
    }
    //creating space for each set/slot within the hashtable
    table->hashSlots = count_calloc(num_slots, sizeof(set_t*));
    table->slotSize = num_slots;
    if(table->hashSlots == NULL){
      return NULL;
    }

    //creating the actual sets/slots within the hashtable
    for(int i = 0; i < table->slotSize; i++){
      table->hashSlots[i] = set_new();
    }
    return table;

  }
  else{
    return NULL;
  }

}

/**************** hashtable_insert ****************/
/* Insert item, identified by key (string), into the given hashtable.
 *
 * Caller provides:
 *   valid pointer to hashtable, valid string for key, valid pointer for item.
 * We return:
 *   false if key exists in ht, any parameter is NULL, or error;
 *   true iff new item was inserted.
 * Notes:
 *   The key string is copied for use by the hashtable; that is, the module
 *   is responsible for allocating memory for a copy of the key string, and
 *   later deallocating that memory; thus, the caller is free to re-use or
 *   deallocate its key string after this call.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
  if(ht != NULL && key != NULL && item != NULL){
    int slotNum = JenkinsHash(key, ht->slotSize);
    //Important: set module checks to see if key already exists and will return false
    //if it already exists.
    //Set module also creates a space in memory and copies the key string
    return set_insert(ht->hashSlots[slotNum], key, item);
  }
  else{
    return false;
  }
}

/**************** hashtable_find ****************/
/* Return the item associated with the given key.
 *
 * Caller provides:
 *   valid pointer to hashtable, valid string for key.
 * We return:
 *   pointer to the item corresponding to the given key, if found;
 *   NULL if hashtable is NULL, key is NULL, or key is not found.
 * Notes:
 *   the hashtable is unchanged by this operation.
 */
void *hashtable_find(hashtable_t *ht, const char *key){
  if(ht == NULL || key == NULL){
    return NULL;
  }

  int slotNum = JenkinsHash(key, ht->slotSize);
  //use set module to find the item. If not found, set_find will return NULL.
  //If found, set_find will return the item.
  return set_find(ht->hashSlots[slotNum], key);
}

/**************** hashtable_print ****************/
/* Print the whole table; provide the output file and func to print each item.
 *
 * Caller provides:
 *   valid pointer to hashtable,
 *   FILE open for writing,
 *   itemprint that can print a single (key, item) pair.
 * We print:
 *   nothing, if NULL fp.
 *   "(null)" if NULL ht.
 *   one line per hash slot, with no items, if NULL itemprint.
 *   otherwise, one line per hash slot, listing (key,item) pairs in that slot.
 * Note:
 *   the hashtable and its contents are not changed by this function,
 */
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)){
  if(fp == NULL){
    return;
  }
  if(ht != NULL){
    for(int i = 0; i < ht->slotSize; i++){
      if(itemprint == NULL){
        fprintf(fp, "This is Slot %d: {}\n", i); //if itemprint is null, print each slot without any of the contents
      }
      else{ //if itemprint is not null, print each slot with the contents of the set
        fprintf(fp, "This is Slot %d", i);
        set_print(ht->hashSlots[i], fp, itemprint);
        //If the set is empty, the contents of the slot will be printed as (null)
      }
    }

  }
  else{
    //if hashtable pointer is null, just print (null)
    fprintf(fp, "(null)\n");
  }

}

/**************** hashtable_iterate ****************/
/* Iterate over all items in the table; in undefined order.
 *
 * Caller provides:
 *   valid pointer to hashtable,
 *   arbitrary void*arg pointer,
 *   itemfunc that can handle a single (key, item) pair.
 * We do:
 *   nothing, if ht==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc once for each item, with (arg, key, item).
 * Notes:
 *   the order in which hashtable items are handled is undefined.
 *   the hashtable and its contents are not changed by this function,
 *   but the itemfunc may change the contents of the item.
 */
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) ){
  if(ht == NULL || itemfunc == NULL){
    return ;
  }
  //if ht and itemfunc are not null iterate over the contents in each slot
  for(int i = 0; i < ht->slotSize; i++){
    set_iterate(ht->hashSlots[i], arg, itemfunc);
  }
}

/**************** hashtable_delete ****************/
/* Delete hashtable, calling a delete function on each item.
 *
 * Caller provides:
 *   valid hashtable pointer,
 *   valid pointer to function that handles one item (may be NULL).
 * We do:
 *   if hashtable==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the hashtable itself.
 * Notes:
 *   We free the strings that represent key for each item, because
 *   this module allocated that memory in hashtable_insert.
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ){
  if(ht == NULL){
    return ;
  }

  for(int i = 0; i < ht->slotSize; i++){
    if(itemdelete != NULL){   //pass itemdelete to set_delete 
      set_delete(ht->hashSlots[i], itemdelete);
    }
  }
  count_free(ht->hashSlots);    //free the memory allocated for the slots
  count_free(ht);               //free the memory allocated for the hashtable

#ifdef MEMTEST
  count_report(stdout, "End of hashtable_delete");
#endif
}
