/*
 * hashtest.c - test program for CS50 hashtable module
 *
 *
 *
 * Ashley Song, CS50, 19x
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <assert.h>
 #include "hashtable.h"
 #include "memory.h"


static void hash_print(FILE *fp, const char *key, void *item);
static void hash_iterate(void *arg, const char *key, void *item);
static void hash_delete(void *item);
static void str_copy(const char *theKey, char *keyCopy);


 int main(){

  hashtable_t *hashnull = hashtable_new(0);
  if(hashnull == NULL){
    fprintf(stderr, "hashtable_new fails with size less than or equal to 0\n");
  }
  //create the hashtable_t with 15 slots
  hashtable_t *hashtb = hashtable_new(15);
  if(hashtb == NULL){
    fprintf(stderr, "hastable_new failed\n");
  }

  printf("Printing new hashtable. Slots should be empty\n");
  hashtable_print(hashtb, stdout, hash_print);
  char *i1 = "favorite";
  char *i2 = "meh";
  char *i3 = "nah";
  char *item1 = count_malloc(strlen(i1) + 1);
  char *item2 = count_malloc(strlen(i2) + 1);
  char *item3 = count_malloc(strlen(i3) + 1);
  str_copy(i1, item1);
  str_copy(i2, item2);
  str_copy(i3, item3);

  printf("Adding key/item pair to hashtable\n");
  char *key1 = "Volleyball";
  assert(hashtable_insert(hashtb, key1, item1) == true);
  char *key2 = "Basketball";
  assert(hashtable_insert(hashtb, key2, item2) == true);
  char *key3 = "Soccer";
  assert(hashtable_insert(hashtb, key3, item3) == true);
  assert(hashtable_insert(hashtb, key3, item2) == false);   //trying to insert duplicate
  char *key4 = "Tennis";
  int item4 = 2;
  assert(hashtable_insert(hashtb, NULL, &item4) == false);   //trying to add with NULL key
  assert(hashtable_insert(hashtb, key4, NULL) == false);     //trying to add with NULL item
  assert(hashtable_insert(NULL, key4, &item4) == false);     //trying to add with NULL hashtable pointer

  int *findItem = hashtable_find(hashtb, key2);
  if(findItem != NULL){
    fprintf(stderr, "Inserted key found.\n");
  }
  char *key5 = "Track";   //a key not in the hashtable
  int *theItem = hashtable_find(hashtb, key5);
  int *theItem2 = hashtable_find(NULL, key5);
  int *theItem3 = hashtable_find(hashtb, NULL);     //testing all NULL and non-existing key patterns
  if(theItem == NULL && theItem2 == NULL && theItem3 == NULL){
    printf("hashtable_find is correctly returning NULL for invalid parameters\n");
  }

  //testing hashtable_print
  printf("testing hashtable_print\n");
  hashtable_print(hashtb, stdout, hash_print);

  //testing hashtable_print with null itemprint pointer
  printf("testing hashtable_print with null itemprint pointer\n");
  hashtable_print(hashtb, stdout, NULL);

  //testing hashtable_print with null hashtable pointer
  printf("testing hashtable_print with null hashtable pointer\n");
  hashtable_print(NULL, stdout, hash_print);

  //testing hashtable_print with null fp
  printf("testing hashtable_print with null fp\n");
  hashtable_print(hashtb, NULL, hash_print);

  printf("Testing hashtable_iterate\n");
  int itemcount = 0;
  hashtable_iterate(hashtb, &itemcount, hash_iterate);
  printf("Number of items in hashtable: %d\n", itemcount);
  //testing iterate with NULL pointers
  printf("Testing hashtable_iterate with null pointers\n");
  hashtable_iterate(NULL, NULL, NULL);

  printf("Deleting hashtable...\n");
  hashtable_delete(hashtb, hash_delete);

  return 0;
 }

 void hash_print(FILE *fp, const char *key, void *item){
  char *setItem = item;
  fprintf(fp, "%s: %s", key, setItem);
 }

 void hash_iterate(void *arg, const char *key, void *item){
   //count number of items in hashtable
   int *numItems = arg;

   if(numItems != NULL && item != NULL && key != NULL){
     (*numItems)++;
   }
 }

 void hash_delete(void *item){
   if (item != NULL){
     count_free(item);
   }
 }

 //taken from CS50 Lecture, used to allocate memory for hard coded tests
 void str_copy(const char *theKey, char *keyCopy){
   while(*theKey != '\0'){
     *keyCopy++ = *theKey++;
   }
   *keyCopy = '\0';
 }
