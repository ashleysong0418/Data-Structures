# CS50 Lab 3
## CS50 Summer 2019

### counters
### Information and formate taken from CS50 lab instructions

A counter set is a set of counters, each distinguished by an integer key. It’s a set - each key can only occur once in the set - but instead of storing (key,item) pairs, it tracks a counter for each key. It starts empty. Each time counters_add is called on a given key, that key’s counter is incremented. The current counter value can be retrieved by asking for the relevant key. (Explanation taken from CS50 set description).


### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, implements a counters_t of `void*`, and exports the following functions (static functions not listed but shown in `counters.c`):

```c
counters_t * counters_new(void);
int counters_add(counters_t *ctrs, const int key);
int counters_get(counters_t *ctrs, const int key);
bool counters_set(counters_t *ctrs, const int key, const int count);
void counters_print(counters_t *ctrs, FILE *fp);
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count));
void counters_delete(counters_t *ctrs);
```

### Implementation

We implement this counters_t as a linked list.
The *counters_t* itself is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the counters_t is empty.

Each node in the list is a `struct counterNode`, a type defined internally to the module.
Each counterNode includes a `int theKey`, `int count` and a pointer to the next counterNode on the list.

To insert, we we create a new counterNode with the count initialized to 1, and insert it at the head of the list.

To get the count from the counters_t we iterate through the list to find the matching node and return the count value.
Of course, if the list is empty or the key not found, we return 0 instead.

the `counters_set` method takes a key value and sets that counter value to the one give by the user. If the key is not in the counter set, a new node is created with the value initialized to the count given by the user.

The `counters_t_print` method prints a little syntax around the list, prints the key and count values.

The `counters_t_iterate` method calls the `itemfunc` function on each counterNode by scanning the linked list.

The `counters_t_delete` method frees each node as it proceeds.
It concludes by freeing the `struct counters_t`.

### Assumptions

No assumptions beyond those that are clear from the spec.

The `count` inserted cannot be negative, and thus a 0 return from `counters_add` or `counters_get` must indicate either error or an invalid input.


### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counterstest.c` - unit test driver
* `TESTING.md` - testing results results

### Compilation

To compile, simply `make`.

### Testing

The `counterstest.c` program has hard-coded test values.
It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply `make test`.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`. It is on by default, but can be commented out.

To test with valgrind, `make valgrind`.
