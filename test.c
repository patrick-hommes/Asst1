#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>

#include "mymalloc.h"

int main(int argc, char * argv[]){
    int a1 = 0, a2 = 0, a3 = 0;
    char * testA[1000];
    int outLoop = 100, inLoop = 1000;
    
    for(a1 = 0; a1 < outLoop; a1++){
        int countMalloc = 0, countNull = 0;
        for (a2 = 0; a2 < inLoop; a2++){
            testA[a2] = (char*)malloc(sizeof(char));
            if(testA[a2] != NULL)
            {
                countMalloc++;
            }
            else{
                countNull++;
            }
        }
        for (a3 = countMalloc-1; a3 > 0; a3--){
            free(testA[a3]);
        }
    errCollect(0, 0, 0, 0, 1);  
    }
}