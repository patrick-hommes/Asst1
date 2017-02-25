#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>

#include "mymalloc.h"

int main(int argc, char * argv[]){
    int a1 = 0, a2 = 0, a3 = 0;
    char * testA[1000];
    char * testB[1000];
    
    printf("\n\nTest A - \n");
    
    for(a1 = 0; a1 < 100; a1++){
        int countMalloc = 0, countNull = 0;
        for (a2 = 0; a2 < 1000; a2++){
            testA[a2] = (char*)malloc(sizeof(char));
            if(testA[a2] != NULL)
            {
                countMalloc++;
            }
            else{
                countNull++;
            }
        }
        for (a3 = 0; a3 < countMalloc; a3++){
            free(testA[a3]);
        }
    }
    errCollect(0, 0, 0, 5, 1);
    
    printf("\nTest B - \n");
    
    for(a1 = 0; a1 < 100; a1++){
        int countMalloc = 0, countFree = 0;
        for(a2 = 0; a2 < 1000; a2++){
            testB[a2] = (char*)malloc(sizeof(char));
            countMalloc++;
            if(testB[a2] != NULL){
                free(testB[a2]);
                countFree++;
            }
        }
    }
    errCollect(0, 0, 0, 5, 1);
}