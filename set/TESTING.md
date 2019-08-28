# CS50 Lab 3
## CS50 Summer 2019
## Ashley Song

### Functionality test 

Various functionality tests are conducted in settest.c:

* TEST 1: creating an empty set
* TEST 2: iterating over empty set
* TEST 3: inserting items into the set with valid parameters
* TEST 4: inserting with null key
* TEST 5: inserting with null set pointer
* TEST 7: finding an item in set
* TEST 8: iterating over set to count number of Items
* TEST 9: printing contents of the set
* TEST 10: printing with null parameters
* TEST 11: delete set


#### Functionality test output
```bash
$ make clean; make test
Count (should be zero): 0
testing set_insert...
Finding 'bbb'
Found pointer for 'bbb': 0x19556b0
Count (should be 3): 3
The set:
{"nah","meh","favorite",}
delete the set...
```

The above output excludes the compilation output with `gcc` and `-DMEMTEST`.


### Memory test
```bash
$ make clean; make valgrind
==9965==
==9965== HEAP SUMMARY:
==9965==     in use at exit: 0 bytes in 0 blocks
==9965==   total heap usage: 11 allocs, 11 frees, 1,133 bytes allocated
==9965==
==9965== All heap blocks were freed -- no leaks are possible
==9965==
==9965== For lists of detected and suppressed errors, rerun with: -s
==9965== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

The above output excludes the compilation output and the test program's normal output.
