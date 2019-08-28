# Makefile for 'Set' module
#
# Ashley Song, CS50, 19X
# Taken from given template from bag.c Makefile

PROG = settest
OBJS = settest.o set.o ../lib/memory.o
LIBS =

# uncomment the following to turn on verbose memory logging
TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

settest.o: set.h ../lib/memory.h
set.o: set.h
memory.o: ../lib/memory.h

.PHONY: test valgrind clean


test: $(PROG)
	@./$(PROG)


valgrind: $(PROG)
	valgrind ./$(PROG)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
