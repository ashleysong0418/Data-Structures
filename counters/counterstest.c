/*
 * counterstest.c - test program for CS50 counters module
 *
 * usage: read lines from stdin
 *
 * CS50, Summer 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "readlinep.h"

static void THEitemcount(void *arg, const int key, const int count);


int main(){
  counters_t *counterSet;

  counterSet = counters_new();
  if (counterSet == NULL){
    fprintf(stderr, "counters_new failed\n");
    exit(1);
  }

  //add counters to counter, all counts should be at 1 for now
  printf("Adding newly initialized counters\n");
  int max = 20;
  for(int i = 2; i <= max; i+=2){
    counters_add(counterSet, i);
  }
  counters_add(NULL, 31);   //testing with null pointer
  counters_add(counterSet, -4);   //testing with negative key

  //print all counters in counterSet after initialization
  printf("PRINTING all newly initialized counters\n");
  counters_print(counterSet, stdout);

  //Testing counters_set function by setting node to 5
  counters_set(counterSet, 8, 5);
  counters_set(counterSet, 4, 10);
  counters_set(counterSet, 5, 9); //a non existing key

  //print all counters in counterSet after setting
  printf("PRINTING counters AFTER setting\n");
  counters_print(counterSet, stdout);

  //Testing counters_get function
  printf("TESTING counter GET function\n");
  int check1 = counters_get(counterSet, 8);
  int check2 = counters_get(counterSet, 4);
  int check3 = counters_get(counterSet, 5);
  int check4 = counters_get(counterSet, 1); //a nonexisting node
  printf("Only check4 should be 0: %d %d %d %d\n", check1, check2, check3, check4 );

  //iterate over and count number of counter
  int theCounts = 0;
  counters_iterate(counterSet, &theCounts, THEitemcount);
  printf("This is the number of counters in the counterSet: %d \n", theCounts);

  //delete everything in counterSet and the counterSet itself
  counters_delete(counterSet);


}
//printing each counter key and count
static void THEitemcount(void *arg, const int key, const int count){

  printf("Key: %d, Count: %d\n", key, count);

}
