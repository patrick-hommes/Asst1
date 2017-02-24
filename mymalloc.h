#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>

#define malloc( x ) myMalloc( x, __FILE__, __LINE__ )
#define free( x ) myFree( x, __FILE__, __LINE__ )

char myBlock[5000];

typedef struct metaData{
    size_t size;
    int isFree;
    struct metaData *next;
}metaData;

metaData *blocksFree = (void*)myBlock;

void createFirstBlock();
void split(metaData *whereBlock, size_t size);
void *myMalloc(size_t bytesNeeded, char *file, int line);
void merge();
void myFree(void *blockPtr, char *file, int line);