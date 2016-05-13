 CC=gcc
CFLAGS=-pedantic -Wall
CFILES=src/index.c src/search.c src/main.c


all: index search

search:
	$(CC) -g $(CFILES) $(CFLAGS) -o search

index:
	$(CC) -g  $(CFLAGS) src/index.c src/indexer.c -o index

clean:
	rm search index
