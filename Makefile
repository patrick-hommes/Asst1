CC = gcc

CFLAGS = -g -Wall

default: memgrind

memgrind: memgrind.o mymalloc.o
		$(CC) $(CFLAGS) -o memgrind memgrind.o mymalloc.o
	
mymalloc.o: mymalloc.c mymalloc.h
		$(CC) $(CFLAGS) -c mymalloc.c
	
clean:
		$(RM) memgrind *.o