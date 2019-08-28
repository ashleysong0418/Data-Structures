# CS50 Lab 3
## CS50 Summer 2019

### Functionality test
### Format and explanations taken from CS50 lab instructions

Various functionality tests are conducted in counterstest.c:

* TEST 1: creating an empty counters_t
* TEST 2: inserting new counterNodes into a valid counters_t
* TEST 3: inserting counterNodes into a null counters_t
* TEST 4: inserting counterNodes into a valid counters with negative key value
* TEST 5: printing all counterNodes in the counters_t
* TEST 6: setting counterNode counts for already existing keys
* TEST 7: setting counterNode counts for a non-existing key
* TEST 8: printing all counterNodes after setting
* TEST 9: testing the counters_get functions
* TEST 10: iterating over the counterNodes to count number of nodes
* TEST 11: deleting all Nodes and the counters_t


#### Functionality test output
```bash
$ make clean; make test
Adding newly initialized counters
PRINTING all newly initialized counters
{20=1,18=1,16=1,14=1,12=1,10=1,8=1,6=1,4=1,2=1,}PRINTING counters AFTER setting
{5=9,20=1,18=1,16=1,14=1,12=1,10=1,8=5,6=1,4=10,2=1,}TESTING counter GET function
Only check4 should be 0: 5 10 9 0
Key: 5, Count: 9
Key: 20, Count: 1
Key: 18, Count: 1
Key: 16, Count: 1
Key: 14, Count: 1
Key: 12, Count: 1
Key: 10, Count: 1
Key: 8, Count: 5
Key: 6, Count: 1
Key: 4, Count: 10
Key: 2, Count: 1
This is the number of counters in the counterSet: 0
```

The above output excludes the compilation output with `gcc` and `MEMTEST`.


### Memory test
```bash
$ make clean; make valgrind
==9417==
==9417== HEAP SUMMARY:
==9417==     in use at exit: 0 bytes in 0 blocks
==9417==   total heap usage: 13 allocs, 13 frees, 1,296 bytes allocated
==9417==
==9417== All heap blocks were freed -- no leaks are possible
==9417==
==9417== For lists of detected and suppressed errors, rerun with: -s
==9417== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

The above output excludes the compilation output and the test program's normal output.
