# Makefile for 'Hashtable' module
#
# Ashley Song, 19X, CS50
# Template from CS50 'bag' module Makefile

PROG = hashtest
OBJS = hashtest.o hashtable.o jhash.o ../lib/memory.o ../set/set.o
LIBS =

# uncomment the following to turn on verbose memory logging
TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtest.o: hashtable.h ../set/set.h
hashtable.o: hashtable.h ../set/set.h
jhash.o: jhash.h
memory.o: ../lib/memory.h
set.o: ../set/set.h


.PHONY: test valgrind clean


test: $(PROG)
	@./$(PROG)


valgrind: $(PROG)
	valgrind ./$(PROG)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
