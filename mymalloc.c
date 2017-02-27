#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>

#include "mymalloc.h"

static char myblock[BLOCKSIZE];
metaData *head = (void*)myblock;

// Variables for error collection
////////////////////
static int totalError = 0;
static int byteReq0 = 0;
static int noAllocate = 0;
static int freeNull = 0;
static int noPointer = 0;
static int alreadyFree = 0;
static int overFlow = 0;

// Just makes the frist block and sets some values
////////////////////
void createFirstBlock()
{
	head->currentSize = BLOCKSIZE - sizeof(metaData);
	head->next = NULL;
	head->isFree = 1;
}


void *mymalloc(size_t size, char * file, int line)
{

	// These two pointers are used to iterate over our linked list
	// of metaData and to help make the next link respectively.
	////////////////////
	metaData *iterationPointer = NULL;
	metaData *newBlock = NULL;

	// If the user enters malloc(0) it'll tell them that this doesn't
	// work
	////////////////////
	if(size == 0)
	{
		errCollect(file, line, 0, 0, 0);
		totalError++;
		return NULL;
	}

	// If head hasn't been used set up yet, create it.
	////////////////////
	if(head->currentSize == 0)
	{
		createFirstBlock();
	}

	// This is the pointer that will be used in the while loop
	////////////////////
	iterationPointer = head;

	while(iterationPointer != NULL)
	{
		// First check if this block is free
		////////////////////
		if(iterationPointer->isFree == 1)
		{
			// If yes, check size of block vs size requested
			////////////////////
			if((iterationPointer->currentSize < size) || (iterationPointer->currentSize < (size + sizeof(metaData))))
			{
				// If too small, move on
				////////////////////
				iterationPointer = iterationPointer->next;
			}
			else{
				// Create a new metaData block and put it right after current
				////////////////////
				newBlock = (void*)((void*)iterationPointer + sizeof(metaData) + size);
				newBlock->isFree = 1;
				newBlock->currentSize = (iterationPointer->currentSize) - sizeof(metaData) - size;

				if(iterationPointer->next == NULL)
				{
					newBlock->next = NULL;
				}
				else
				{
					newBlock->next = iterationPointer->next;
				}
				// Updates to block of memory that will be returned
				////////////////////
				iterationPointer->currentSize = size;
				iterationPointer->next = newBlock;
				iterationPointer->isFree = 0;
				
				// Return where the pointer is + a bit so we don't
				// write over the metaData
				////////////////////
				return (void *)((void*)iterationPointer + sizeof(metaData));
				}
			}
		else
		{
			iterationPointer = iterationPointer->next;
		}
	}	
	errCollect(file, line, (int)size, 1, 0);
	totalError++;
	return NULL;
}

void myfree(void *memoryPtr, char *file, int line)
{
	if(memoryPtr == NULL)
	{
		errCollect(file, line, 0, 2, 0);
		totalError++;
		return;
	}
	// Takes the pointer you were given and attempts to make it point to the
	// metaData
	////////////////////
	metaData * ptr = memoryPtr - sizeof(metaData);

	//  Part of a check to see if the pointer that was given, is something 
	// that our malloc program had alloc'd. Work in progress at the moment.
	////////////////////
	if(!withinBounds(ptr))
	{
		errCollect(file, line, 0, 3, 0);
		totalError++;
		return;
	}
	
	if(ptr->isFree)
	{
		errCollect(file, line, 0, 4, 0);
		totalError++;
		return;
	}

	// If the pointer is pointing to metaData and it isn't already free
	// set the variable to free then attempts to clean up memory next to it.
	////////////////////
	ptr->isFree = 1;
	merge();
	
}

int withinBounds(void * ptr)
{
	return (void*)ptr >= (void*)myblock && (void*)ptr < (void*)myblock + BLOCKSIZE;
}

void merge()
{
	metaData *ptr;
	ptr = head;
	while(ptr != NULL)
	{
		if(ptr->isFree && (ptr->next != NULL) && ptr->next->isFree)
		{
			ptr->currentSize += ptr->next->currentSize + sizeof(metaData);
			ptr->next = ptr->next->next;
		}
		ptr = ptr->next;
	}
}

void errCollect(char * file, int line, int size, int code, int final){
	
	// Intakes error codes from mymalloc and myfree functions.
	// Prints the first occurance of an error, then counts times
	// it repeats.
	////////////////////
	

	if (code == 0){
		if (byteReq0 < 1){
			printf("User requested 0 bytes in file: %s, line: %d\n",file , line);
		}
		byteReq0++;
	}
	else if (code == 1){
		overFlow = overFlow + size;
		if (noAllocate < 1){
			printf("Not enough memory to allocate %d bytes in file: %s, line: %d\n", size, file, line);
		}
		noAllocate++;
	}
	else if (code == 2){
		if (freeNull < 1){
			printf("Tried to free NULL in file: %s, line: %d\n", file, line);
		}
		freeNull++;
	}
	else if (code == 3){
		if (noPointer < 1){
			printf("Pointer not allocted by a malloc call from file: %s, line: %d\n", file, line);
		}
		noPointer++;
	}
	else if (code == 4){
		if (alreadyFree < 1){
			printf("Attempted to free a pointer already free in file: %s, line: %d\n", file, line);
		}
		alreadyFree++;
	}

	// From test file  errCollect(0,0,0,5,1) signifies the end of a test
	// and all errors collected during the test are then reported in
	// total.
	////////////////////
	
	if (final == 1){
		if (totalError == 0){
			printf("No errors found.\n");
		}
		else if(totalError > 0){
			printf("A total of %d error(s) were collected.\n", totalError);
		}
		if (byteReq0 > 0){
			printf("User requested 0 bytes %d times.\n", byteReq0);
		}
		if (noAllocate > 0){
			printf("User requested a total of %d bytes over %d attempts\n", overFlow, noAllocate);
			printf("	that could not be allocated in available space.\n");
		}
		if (freeNull > 0){
			printf("User attempted to free NULL %d times.\n", freeNull);
		}
		if (alreadyFree > 0){
			printf("User tried to free an already free pointer %d times\n", alreadyFree);
		}
		printf("Final size of data block %d\n", ((int)head->currentSize));
		final = 0;
		overFlow = 0;
		totalError = 0;
		byteReq0 = 0;
		noAllocate = 0;
		freeNull = 0;
		alreadyFree = 0;
	}
}