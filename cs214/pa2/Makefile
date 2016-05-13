OBJS= sorted-list.o mainint.o maindouble.o mainstring.o

CC= gcc

CFLAGS = -Wall -g

clean:
	rm -f sl $(OBJS) libsl.a
libsl.a: sorted-list.o
	ar -r libsl.a sorted-list.o
sorted-list.o: sorted-list.c sorted-list.h
	$(CC) -c $(CFLAGS) sorted-list.c



mains:
	$(CC) -c $(CLAGS) mainint.c
	$(CC) -c $(CLAGS) maindouble.c
	$(CC) -c $(CLAGS) mainstring.c
lib:
	gcc -c sorted-list.c
	ar rcs libsl.a sorted-list.o

