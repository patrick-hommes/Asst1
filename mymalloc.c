#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>

#include "mymalloc.h"

void createFirstBlock(){
    blocksFree->size = 5000 - sizeof(metaData);
    blocksFree->isFree = 1;
    blocksFree->next = NULL;
}

void *myMalloc(size_t bytesNeeded,char *file, int line){
    metaData *ptr;
    
    if(!(blocksFree->size)){
        createFirstBlock();
    }
    
    ptr = blocksFree;
    
    while((ptr->size)||(((ptr->isFree)==0)&&(ptr->next!=NULL))){
        ptr = ptr->next;
    }
    
    if((ptr->size)==bytesNeeded){
        ptr->isFree = 0;
    }
    else if((ptr->size)>(bytesNeeded + sizeof(metaData))){
        split(ptr,bytesNeeded);
    }
    else{
        printf("Not enough memory.\n");
    }
    return 0;
}

void myFree(void *blockPtr, char *file, int line){
    if(((void*)myBlock<=blockPtr)&&(blockPtr<=(void*)(myBlock+sizeof(metaData)))){
        metaData* ptr = blockPtr;
        --ptr;
        ptr->isFree = 1;
        merge();
    }
}

void split(metaData *whereBlock, size_t size){
    metaData *newBlock = (void*)((void*)whereBlock + sizeof(metaData) + size);
    newBlock->size = ((whereBlock->size) - sizeof(metaData) - size);
    newBlock->isFree = 1;
    newBlock->next = whereBlock->next;
    whereBlock->size = size;
    whereBlock->isFree = 0;
    whereBlock->next = newBlock;
}

void merge(){
    metaData *ptr;
    ptr = blocksFree;
    while((ptr->next)!=NULL){
        if((ptr->isFree)&&(ptr->next->isFree)){
            ptr-> size += (ptr->next->size)+sizeof(metaData);
            ptr->next = ptr->next->next;
        }
        ptr=ptr->next;
    }
}

