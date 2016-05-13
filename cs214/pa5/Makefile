CC = gcc
CCFLAGS = -Wall -pthread -g
ARKEYS = rv
TARGET = book_order

all: book_order

book_order:  
	$(CC) $(CCFLAGS) queue.c thread_functions.c book_order.c -o book_order

#book_order.o: book_order.c
#	$(CC) $(CCFLAGS) -c book_order.c
#
#thread_functions.o: thread_functions.c
#	$(CC) $(CCFLAGS) -c thread_functions.c
#
#queue.o: queue.c
#	$(CC) $(CCFLAGS) -c queue.c
#
clean:
	rm -f sl *.o book_order
