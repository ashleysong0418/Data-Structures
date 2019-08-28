# Makefile for 'Counters' module
#
# Ashley Song, CS50, Lab3, 19X
#Template from CS50 'bag' module


PROG = counterstest
OBJS = counterstest.o counters.o ../lib/readlinep.o ../lib/memory.o
LIBS =

#uncomment the following to turn on verbose memory logging
TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterstest.o: counters.h ../lib/readlinep.h
counters.o: counters.h
readline.o: ../lib/readlinep.h

.PHONY: test valgrind clean

test: $(PROG)
	@./$(PROG)


valgrind: $(PROG)
	valgrind ./$(PROG)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
