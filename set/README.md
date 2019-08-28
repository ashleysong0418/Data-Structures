# CS50 Lab 3
## CS50 Summer 2019
## Ashley Song
### set
### Information and formate taken from CS50 lab instructions

A `set` maintains an unordered collection of _(key,item)_ pairs; any given key can only occur in the set once. It starts out empty and grows as the caller inserts new _(key,item)_ pairs. The caller can retrieve items by asking for their key, but cannot remove or update pairs. Items are distinguished by their key. (Explanation taken from CS50 set description).

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `void*`, and exports the following functions (static functions not listed but shown in `set.c`):

```c
set_t *set_new(void);
bool set_insert(set_t *set, const char *key, void *item);
void *set_find(set_t *set, const char *key);
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) );
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) );
void set_delete(set_t *set, void (*itemdelete)(void *item) );
```

### Implementation

We implement this set as a linked list.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setNode`, a type defined internally to the module.
Each setNode includes a pointer to the `void *item`, `char *key` and a pointer to the next setNode on the list.

To insert a new item in the set we create a new setNode to hold the `item`, and insert it at the head of the list.

To find an item from the set we iterate through the list using a for loop and return the _item_.
Of course, if the list is empty, we return NULL instead.

The `set_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by scanning the linked list. If not `itemprint` is given, the set is printed with no _item_.

The `set_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `set_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing setNodes as it proceeds.
It concludes by freeing the `struct set`.

### Assumptions

No assumptions beyond those that are clear from the spec.

The `item` inserted cannot be NULL, and thus a NULL return from `set_find` must indicate no item in the set with the given key, not simply a NULL `item` coming out of the set.

Though the `set` is implemented as a Linked List, it is not a stack, in comparison to `bag`. No extract function is included in the implementation.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver
* `TESTING.md` - testing results results

### Compilation

To compile, simply `make`.

### Testing

The `settest.c` program is hard-coded for examples and puts the items in the set.
It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done.

To test, simply `make test`.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`. It is on by default, but can be commented out.

To test with valgrind, `make valgrind`.
