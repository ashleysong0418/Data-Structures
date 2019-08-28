/*
 * settest.c - test program for CS50 set module
 *
 * 
 *
 * Ashley Song, CS50, 19x
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "memory.h"
#include "set.h"
#include "readlinep.h"

static void itemcount(void *arg, const char *key, void *item);
static void nameprint(FILE *fp, const char *key, void *item);
static void delete(void *item);
static void str_copy(const char *theKey, char *keyCopy);


int main(){
  set_t *set;
  int itemCount = 0;

  //create a new set data structure
  set = set_new();
  if (set == NULL) {
    fprintf(stderr, "set_new failed\n");
    return 1;
  }
  printf("Count (should be zero): ");
  set_iterate(set, &itemCount, itemcount);
  printf("%d\n", itemCount);

  printf("testing set_insert...\n");
  char *i1 = "favorite";
  char *i2 = "meh";
  char *i3 = "nah";
  char *item1 = count_malloc(strlen(i1) + 1);
  char *item2 = count_malloc(strlen(i2) + 1);
  char *item3 = count_malloc(strlen(i3) + 1);
  str_copy(i1, item1);
  str_copy(i2, item2);
  str_copy(i3, item3);
  char *key1 = "aaa";

  assert(set_insert(set, key1, item1) == true);
  char *key2 = "bbb";

  assert(set_insert(set, key2, item2) == true);
  char *key3 = "ccc";

  assert(set_insert(set, key3, item3) == true);
  char *key4 = NULL;
  char *name4 = "emily";
  assert(set_insert(set, key4, name4) == false);
  char *key5 = "ddd";
  char *name5 = NULL;
  assert(set_insert(set, key5, name5) == false);

  assert(set_insert(NULL, key5, name5) == false);

  itemCount = 3;    //3, because three of them should not insert

  printf("Finding 'bbb'\n");
  char *found = set_find(set, key2);
  printf("Found pointer for 'bbb': %p\n", found);

  printf("Count (should be %d): ", itemCount);
  itemCount = 0;
  set_iterate(set, &itemCount, itemcount);
  printf("%d\n", itemCount);

  printf("The set:\n");
  set_print(set, stdout, nameprint);
  printf("\n");
  set_print(NULL, NULL, NULL);

  printf("delete the set...\n");
  set_delete(set, delete);

  return 0;
}

// print items of each node in set, in quotes
//key is not used here
void nameprint(FILE *fp, const char *key, void *item)
{
  char *name = item;
  if (name == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "\"%s\"", name);
  }
}

/* count the nodes with non-null items/keys in the bag.
 * note here we don't care what kind of item is in bag.
 */
static void itemcount(void *arg, const char *key, void *item)
{
  int *numItems = arg;

  if (numItems != NULL && item != NULL && key != NULL)
    (*numItems)++;
}

void delete(void *item){
  if (item != NULL){
    count_free(item);
  }
}

//taken from CS50 Lecture, used in set.c as well. Needed for hard-code in driver
void str_copy(const char *theKey, char *keyCopy){
  while(*theKey != '\0'){
    *keyCopy++ = *theKey++;
  }
  *keyCopy = '\0';
}
