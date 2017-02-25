#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define BLOCKSIZE 5000

typedef struct metaData
{
	struct metaData *next;
	int isFree;
	size_t currentSize;
}metaData;

void * mymalloc(size_t size, char * file, int line);
void myfree(void *blockPtr, char * file, int line);
void display();
int valid(metaData * ptr);
void createFirstBlock();
void merge();
int withinBounds(void * ptr);
void errCollect(char * file, int line, int size, int code, int final);