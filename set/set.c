/*
 * set.c file
 *Take from set.h template:
 * A *set* maintains an unordered collection of (key,item) pairs;
 * any given key can only occur in the set once. It starts out empty
 * and grows as the caller inserts new (key,item) pairs.  The caller
 * can retrieve items by asking for their key, but cannot remove or
 * update pairs.  Items are distinguished by their key.
 *
 * Ashley Song, CS50, 19x, Lab3 Sets
 *
 */

// #ifndef __SET_H
// #define __SET_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#include "memory.h"

/**************** local types ****************/
typedef struct setNode {
  void *item;
  char *key;
  struct setNode *next;
} setNode_t;

/**************** global types ****************/
// opaque to users of the module
typedef struct set {
  struct setNode *head;
} set_t;

/**************** functions ****************/
static setNode_t *setNode_new(char *key, void *item);
static void str_copy(const char *theKey, char *keyCopy);

/**************** set_new ****************/
/* Create a new (empty) set.
 *
 * We return:
 *   pointer to a new set, or NULL if error.
 * We guarantee:
 *   The set is initialized empty.
 * Caller is responsible for:
 *   later calling set_delete.
 */
set_t *set_new(void){
  set_t *set = count_malloc(sizeof(set_t));

  if(set == NULL) {
    return NULL;
  }
  else{
    set->head = NULL;   //initializing bag to empty
    return set;
  }


}

/**************** setNode_new ****************/
/* Allocate and initialize a setNode */
/* Not visible outside of this file */
/* Initialize count to 1 for each new node*/
static setNode_t * // not visible outside this file
setNode_new(char *key, void *item){
  setNode_t *node = count_malloc(sizeof(setNode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  }

  else{
    node->item = item;
    node->key = key;    //do I need to copy over the string from given key? or
    return node;
  }
}

/**************** set_insert ****************/
/* Insert item, identified by a key (string), into the given set.
 *
 * Caller provides:
 *   valid set pointer, valid string pointer, and pointer to item.
 * We return:
 *  false if key exists, any parameter is NULL, or error;
 *  true iff new item was inserted.
 * Caller is responsible for:
 *   later calling set_delete to free the memory used by key strings.
 * Notes:
 *   The key string is copied for use by the set; that is, the module
 *   is responsible for allocating memory for a copy of the key string, and
 *   later deallocating that memory; thus, the caller is free to re-use or
 *   deallocate its key string after this call.
 */
bool set_insert(set_t *set, const char *key, void *item){
  if(set == NULL || key == NULL || item == NULL){
    return false;
  }
  if(set_find(set, key) == NULL){
    char *nodeKey = count_malloc(strlen(key) + 1);
    if(nodeKey == NULL){
      return false;
    }
    str_copy(key, nodeKey);
    setNode_t *new = setNode_new(nodeKey, item);
    if(new != NULL){
      new->next = set->head;
      set->head = new;
      return true;
    }
  }
  return false;
}


//taken from CS50 Lecture
void str_copy(const char *theKey, char *keyCopy){
  while(*theKey != '\0'){
    *keyCopy++ = *theKey++;
  }
  *keyCopy = '\0';
}

/**************** set_find ****************/
/* Return the item associated with the given key.
 *
 * Caller provides:
 *   valid set pointer, valid string pointer.
 * We return:
 *   a pointer to the desired item, if found;
 *   NULL if set is NULL, key is NULL, or key is not found.
 * Notes:
 *   The item is *not* removed from the set.
 *   Thus, the caller should *not* free the pointer that is returned.
 */
void *set_find(set_t *set, const char *key){
  if(set == NULL || key == NULL){
    return NULL;
  }

  for(setNode_t *node = set->head; node != NULL; node = node->next){  //iterate through and find key
    if(strcmp(key, node->key) == 0){
      return node->item;   //key was found, return node's item
    }
  }

  return NULL;    //if key is not found

}

/**************** set_print ****************/
/* Print the whole set; provide the output file and func to print each item.
 *
 * Caller provides:
 *   valid set pointer,
 *   FILE open for writing,
 *   valid pointer to function that prints one item.
 * We print:
 *   nothing if NULL fp. Print (null) if NULL set.
 *   print a set with no items if NULL itemprint.
 *  otherwise,
 *   print a comma-separated list of items surrounded by {brackets}.
 * Notes:
 *   The set and its contents are not changed.
 *   The 'itemprint' function is responsible for printing (key,item).
 */
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) ){
  if(fp == NULL){
    return;
  }
  if(set == NULL){
    fputc('{', fp);
    fputs("(null)", fp);
  }
  else{
    fputc('{', fp);
    for (setNode_t *node = set->head; node != NULL; node = node->next) {
      if(itemprint != NULL){
        (*itemprint)(fp, node->key, node->item);
        fputc(',', fp);
      }
    }
  }
  fputc('}', fp);
}

/**************** set_iterate ****************/
/* Iterate over the set, calling a function on each item.
 *
 * Caller provides:
 *   valid set pointer,
 *   arbitrary argument (pointer) that is passed-through to itemfunc,
 *   valid pointer to function that handles one item.
 * We do:
 *   nothing, if set==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc on each item, with (arg, key, item).
 * Notes:
 *   the order in which set items are handled is undefined.
 *   the set and its contents are not changed by this function,
 *   but the itemfunc may change the contents of the item.
 */
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) ){
  if(set==NULL || itemfunc == NULL){
    return;
  }
  for (setNode_t *node = set->head; node != NULL; node = node->next) {
    (*itemfunc)(arg, node->key, node->item);
  }
}

/**************** set_delete ****************/
/* Delete set, calling a delete function on each item.
 *
 * Caller provides:
 *   valid set pointer,
 *   valid pointer to function that handles one item (may be NULL).
 * We do:
 *   if set==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the set itself.
 * Notes:
 *   We free the strings that represent key for each item, because
 *   this module allocated that memory in set_insert.
 */
void set_delete(set_t *set, void (*itemdelete)(void *item) ){
  if(set != NULL){
    for(setNode_t *node = set->head; node!=NULL; ){
      if(itemdelete != NULL){
        (*itemdelete)(node->item);
      }
      setNode_t *next = node->next;
      count_free(node->key);
      count_free(node);
      node = next;

    }
    count_free(set);
  }
#ifdef MEMTEST
  count_report(stdout, "End of set_delete");
#endif
}
