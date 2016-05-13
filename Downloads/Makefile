COMPILER = gcc
CCFLAGS = -Wall -g

all: index

index.o: indexer.c indexer.h tokenizer.c tokenizer.h
		$(COMPILER) $(CCFLAGS) -c indexer.c indexer.h tokenizer.c tokenizer.h
		
tokenizer.o: tokenizer.c tokenizer.h
		$(COMPILER) $(CCFLAGS) -c tokenizer.c tokenizer.h
		
index: index.o tokenizer.o
		$(COMPILER) $(CCFLAGS) -o index index.o tokenizer.o
		
clean:
		rm -f *.o
		rm -f index
		rm -f *.h.gch
