# CS50 Lab 3
## CS50 Summer 2019
##Ashley Song

### Functionality test

Various functionality tests are conducted in hashtest.c:

* TEST 1: creating an empty hashtable, making sure it is not initialized if     size is less then or equal to 0
* TEST 2: printing an empty hashtable
* TEST 3: inserting key/item pairs into hashtable
* TEST 4: inserting a duplicate into a hashtable
* TEST 5: inserting with a NULL key
* TEST 6: inserting with a NULL item
* TEST 7: inserting with a NULL hashtable
* TEST 8: finding an item in a hashtable with valid key
* TEST 9: finding a key/item not in the table
* TEST 10: finding with a NULL hashtable
* TEST 11: finding with a null key value
* TEST 12: testing print function with valid parameters
* TEST 13: testing print with a null itemprint pointer
* TEST 14: testing print with a null hashtable pointer
* TEST 15: testing print with a null fp
* TEST 16: testing iterate with valid parameters
* TEST 17: testing iterate with null parameters
* TEST 18: testing delete function with a valid bag


#### Functionality test output
```bash
$ make clean; make test
hashtable_new fails with size less than or equal to 0
Printing new hashtable. Slots should be empty
This is Slot 0{}This is Slot 1{}This is Slot 2{}This is Slot 3{}This is Slot 4{}This is Slot 5{}This is Slot 6{}This is Slot 7{}This is Slot 8{}This is Slot 9{}This is Slot 10{}This is Slot 11{}This is Slot 12{}This is Slot 13{}This is Slot 14{}Adding key/item pair to hashtable
Inserted key found.
hashtable_find is correctly returning NULL for invalid parameters
testing hashtable_print
This is Slot 0{}This is Slot 1{}This is Slot 2{}This is Slot 3{}This is Slot 4{}This is Slot 5{Volleyball: favorite,}This is Slot 6{}This is Slot 7{}This is Slot 8{Basketball: meh,}This is Slot 9{}This is Slot 10{}This is Slot 11{Soccer: nah,}This is Slot 12{}This is Slot 13{}This is Slot 14{}testing hashtable_print with null itemprint pointer
This is Slot 0: {}
This is Slot 1: {}
This is Slot 2: {}
This is Slot 3: {}
This is Slot 4: {}
This is Slot 5: {}
This is Slot 6: {}
This is Slot 7: {}
This is Slot 8: {}
This is Slot 9: {}
This is Slot 10: {}
This is Slot 11: {}
This is Slot 12: {}
This is Slot 13: {}
This is Slot 14: {}
testing hashtable_print with null hashtable pointer
(null)
testing hashtable_print with null fp
Testing hashtable_iterate
Number of items in hashtable: 3
Testing hashtable_iterate with null pointers
Deleting hashtable...
```

The above output excludes the compilation output with `gcc` and `-DMEMTEST`.


### Memory test
```bash
$ make clean; make valgrind
==5089==
==5089== HEAP SUMMARY:
==5089==     in use at exit: 0 bytes in 0 blocks
==5089==   total heap usage: 27 allocs, 27 frees, 1,398 bytes allocated
==5089==
==5089== All heap blocks were freed -- no leaks are possible
==5089==
==5089== For lists of detected and suppressed errors, rerun with: -s
==5089== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

The above output excludes the compilation output and the test program's normal output.
