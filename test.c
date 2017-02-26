#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>

#include "mymalloc.h"

int main(int argc, char * argv[]){
    int a1 = 0, a2 = 0, a3 = 0;
    char * testA[1000];
    char * testB[1000];
    char * testC[2000];
    int totalMalloc = 0, totalFree = 0, validMalloc = 0;
    int randomNum = 0, totalSwap = 0;
    
    printf("\n\nTest A - (malloc * 1000 then free * 1000) * 100...\n\n");
    
    for(a1 = 0; a1 < 100; a1++){
        int countMalloc = 0, countNull = 0;
        for (a2 = 0; a2 < 1000; a2++){
            testA[a2] = (char*)malloc(sizeof(char));
            totalMalloc++;
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
            totalFree++;
        }
        validMalloc = validMalloc + countMalloc;
    }
    errCollect(0, 0, 0, 5, 1);
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total valid calls to malloc: %d\n", validMalloc);
    printf("Total calls to free: %d\n", totalFree);
    
    printf("\nTest B - (malloc then free * 1000) * 100...\n");
    totalMalloc = 0, totalFree = 0, validMalloc = 0;
    
    for(a1 = 0; a1 < 100; a1++){
        int countMalloc = 0, countFree = 0;
        for(a2 = 0; a2 < 1000; a2++){
            testB[a2] = (char*)malloc(sizeof(char));
            countMalloc++;
            totalMalloc++;
            if(testB[a2] != NULL){
                free(testB[a2]);
                countFree++;
                totalFree++;
            }
        }
        validMalloc = validMalloc + countMalloc;
    }
    errCollect(0, 0, 0, 5, 1);
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total valid calls to malloc: %d\n", validMalloc);
    printf("Total calls to free: %d\n", totalFree);
    
    printf("\nTest C - (random 1 byte malloc or free * 100) * 100...\n");
    totalMalloc = 0, totalFree = 0, validMalloc = 0;
    for (a1 = 0; a1 < 100; a1++){
        int countMalloc = 0, countFree = 0, leftover = 0, isMalloc = 0;
        for (a2 = 0; countMalloc < 1000; a2++){
            randomNum = rand() % 100 + 1;
            if(randomNum <= 50){
                testC[a2] = (char*)malloc(sizeof(char));
                totalMalloc++;
                isMalloc++;
                countMalloc++;
            }
            else if(randomNum >= 51){
                if(isMalloc > 0){
                    free(testC[a2]);
                    totalFree++;
                    countFree++;
                    isMalloc--;
                    a2--;
                }
                else if(isMalloc < 1){
                    testC[a2] = (char*)malloc(sizeof(char));
                    totalMalloc++;
                    countMalloc++;
                    isMalloc++;
                    totalSwap++;
                }
            }
        }
        leftover = countMalloc - countFree;
        if(leftover > 0){
            for(a3 = 0; a3 < leftover; a3++){
                free(testC[a2]);
                totalFree++;
            }
        }
    }
    errCollect(0, 0, 0, 5, 1);
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total calls to free: %d\n", totalFree);
    printf("Total calls to free swapped to malloc: %d\n", totalSwap);
    
    
}