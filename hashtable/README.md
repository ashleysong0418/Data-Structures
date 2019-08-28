# CS50 Lab 3
## CS50 Summer 2019
## Ashley Song

### hashtable

A `hashtable` is a set of (key,item) pairs. It acts just like a set, but is far more efficient for large collections..
The `hashtable` starts empty.
It could be empty, or could contain hundreds of _items_.
_Items_ are indistinguishable, so the _extract_ function is free to return any _item_ from the `hashtable`.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a hashtable of `void*`, and exports the following functions:

```c
hashtable_t *hashtable_new(void);
void hashtable_insert(hashtable_t *ht, const char *key, void *item);
void *hashtable_find(hashtable_t *ht, const char *key);
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item));
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) );
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) );
```

### Implementation

We implement this hashtable using the `set` structure.
The *hashtable* itself is represented as a `struct hashtable` that has an array of pointers that point to a `set`.

Each set in the `hashtable` is a `struct set`, a type defined internally in the module.
Each set includes a pointer to the `setNode *head` and each `setNode` points to a `void *item`, `char *key`, and a `struct setNode *next`.

To insert a new item in the hashtable we create a new set to hold the key/item pair within a `setNode`. A hash key is created using the `jhash.h` module, which is then used to hash into the `hashtable` and insert the key/item pair using `set_insert`.

To find an item from the hashtable we use the `JenkinsHash` function in the `jhash.h` module to then hash into the hashtable and use `set_find` to return the item.
Of course, if the item is found, we return `NULL`.

The `hashtable_print` method prints a little syntax around the list, and between items, but mostly calls the `set_print` function on each slot which then calls the `itemprint`. If an `itemprint` function is not provided, then it prints the slots without any of the items in them.

The `hashtable_iterate` method calls the set_iterate function on each slot by, which is then passed on to the `itemfunc` provided by the user.

The `hashtable_delete` method calls the `set_delete` function for each slot, which then calls the `itemdelete` function provided by the user. Each item is removed, then the slots and the `hashtable` itself using the `count_free` method provided by the `memory.h` module.


### Assumptions

No assumptions beyond those that are clear from the spec.

The `item`, `key`, inserted cannot be NULL, and thus a NULL return from `hashtable_insert` must indicate an error.

Finally, the number of slots given when initializing the *hashtable* must be greater than 0.

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hashtest.c` - unit test driver
* `TESTING.md` - testing results results

### Compilation

To compile, simply `make` in the directory.

### Testing

The `hashtest.c` program utilizes hard coded examples and puts them into a hashtable.
It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply `make test`.

Try testing with `MEMTEST`, which is in the Makefile by default. Comment it out if not needed.

To test with valgrind, `make valgrind`.
