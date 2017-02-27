#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <time.h>
#include "mymalloc.h"

int gettimeofday(struct timeval *tv, struct timezone *tz);

int main(int argc, char * argv[]){
    int a1 = 0, a2 = 0, a3 = 0;
    char * testA[1000];
    char * testB[1000];
    char * testC[1000];
    char * testD[1000];
    char * testE[1000];
    char * testF[1000];
    int totalMalloc = 0, totalFree = 0, validMalloc = 0;
    int randomNum = 0, randomNum2 = 0, totalSwap = 0;
    int totalBytes = 0;
    struct timeval t0, t1;
    long elapsed; 
    double average = 0;
    long double total = 0;
    
    printf("\n\nTest A - (malloc * 1000 then free * 1000) * 100...\n\n");
    
    for(a1 = 0; a1 < 100; a1++){
        gettimeofday(&t0, 0);
        int countMalloc = 0, countNull = 0;  //initialize in loop counters
        for (a2 = 0; a2 < 1000; a2++){
            testA[a2] = (char*)malloc(sizeof(char));  //call malloc funxtion
            totalMalloc++;      //counts all mallocs in inner and outer loop
            if(testA[a2] != NULL)  //checks that malloc function ran with no errors
            {
                countMalloc++;  //counts valid runs
            }
            else{
                countNull++;  //counts runs with errors
            }
        }
        for (a3 = countMalloc - 1; a3 >= 0; a3--){  //stepping backwards frees all valid mallocs
            free(testA[a3]);
            totalFree++;  //counts total free calls
        }
        validMalloc = validMalloc + countMalloc;  //counts total number of valid malloc calls
        gettimeofday(&t1, 0);
        elapsed = (t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec;
        total += elapsed;
    }
    errCollect(0, 0, 0, 5, 1);
    average = total/100;
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total valid calls to malloc: %d\n", validMalloc);
    printf("Total calls to free: %d\n", totalFree);
    printf("Average time of execution: %lf ms.\n", average);
    
    printf("\nTest B - (malloc then free * 1000) * 100...\n\n");
    totalMalloc = 0, totalFree = 0, validMalloc = 0, total = 0;
    
    for(a1 = 0; a1 < 100; a1++){
        gettimeofday(&t0, 0);
        int countMalloc = 0;
        for(a2 = 0; a2 < 1000; a2++){
            testB[a2] = (char*)malloc(sizeof(char));  //call malloc
            totalMalloc++;  //  Total calls
            if(testB[a2] != 0){  
                countMalloc++;  //  Valid calls
                free(testB[a2]);  //  Call free
                totalFree++;  //  Total frees
            }
        }
        validMalloc = validMalloc + countMalloc;
        gettimeofday(&t1, 0);
        elapsed = (t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec;
        total += elapsed;
    }
    errCollect(0, 0, 0, 5, 1);
    average = total/100;
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total valid calls to malloc: %d\n", validMalloc);
    printf("Total calls to free: %d\n", totalFree);
    printf("Average time of execution: %lf ms.\n", average);
    
    printf("\nTest C - (random 1 byte malloc or free * 100) * 100...\n\n");
    totalMalloc = 0, totalFree = 0, validMalloc = 0, total = 0;
    
    for (a1 = 0; a1 < 100; a1++){
        gettimeofday(&t0, 0);
        int countMalloc = 0, countFree = 0, leftover = 0, isMalloc = 0;
        for (a2 = 0; countMalloc < 1000; a2++){
            randomNum = rand() % 100 + 1; //random for free or malloc
            if(randomNum <= 50){  //First random 1-50 then call malloc
                testC[isMalloc] = (char*)malloc(sizeof(char));  //Call malloc
                totalMalloc++;  //total malloc
                isMalloc++; //there is a malloc
                countMalloc++;
            }
            else{ //random 51-100 call free
                if(isMalloc >= 1){  // check for a malloc, if call free
                    isMalloc--;
                    free(testC[isMalloc]); 
                    totalFree++;
                    countFree++;
                }
                else if(isMalloc < 1){ //  check for a malloc, if not call malloc
                    testC[isMalloc] = (char*)malloc(sizeof(char));
                    totalMalloc++;
                    isMalloc++;
                    countMalloc++;
                    totalSwap++; //total times a free was rolled but changed to malloc
                }
            }
        }
        leftover = (countMalloc - countFree);  //checks for more malloc calls then free
        if(leftover > 0){
            for(a3 = leftover - 1; a3 >= 0; a3--){ // runs free for any remaining malloc calls
                free(testC[a3]);
                totalFree++;
            }
        }
        gettimeofday(&t1, 0);
        elapsed = (t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec;
        total += elapsed;
    }
    errCollect(0, 0, 0, 5, 1);
    average = total/100;
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total calls to free: %d\n", totalFree);
    printf("Total calls to free swapped to malloc: %d\n", totalSwap);
    printf("Average time of execution: %lf ms.\n", average);
    
    printf("\nTest D - (random *random* byte malloc or free * 100) * 100...\n\n");
    totalMalloc = 0, totalFree = 0, validMalloc = 0, total = 0;
    for (a1 = 0; a1 < 100; a1++){
        gettimeofday(&t0, 0);
        int countMalloc = 0, countNull = 0, countFree = 0, leftover = 0, isMalloc = 0;
        for (a2 = 0; countMalloc < 1000; a2++){
            randomNum = rand() % 100 + 1; //random for free or malloc
            randomNum2 = rand() % 64 + 1; //random for 1-64 bytes requested
            if(randomNum <= 50){  // first random 1-50 call malloc
                testD[isMalloc] = (char*)malloc((int)randomNum2); //call malloc with value of random2
                if(testD[isMalloc] != NULL)//checks for valid call
                {
                    isMalloc++;
                    countMalloc++;
                    totalMalloc++;
                }
                else{
                    countNull++; // counts invalid calls
                }
                totalBytes = totalBytes + randomNum2;//total bytes requested accross valid and invalid calls
            }
            else{//second random 51-100 call free
                if(isMalloc >= 1){ //checks for malloc if free
                    isMalloc--;
                    free(testD[isMalloc]); // call free
                    totalFree++;
                    countFree++;
                }
                else if(isMalloc < 1){//checks for malloc if not call malloc
                    testD[isMalloc] = (char*)malloc((int)randomNum2); //call malloc
                    if(testD[isMalloc] != NULL)//check for valid malloc
                    {
                        isMalloc++;
                        countMalloc++;
                        totalMalloc++;
                     }
                     else{
                        countNull++;
                    }
                    totalBytes = totalBytes + randomNum2;
                    totalSwap++;//total times free called but malloc needed instead
                }
            }
        }
        leftover = (countMalloc - countFree);//clean up any additional mallocs not freed
        if(leftover > 0){
            for(a3 = leftover - 1; a3 >= 0; a3--){
                free(testD[a3]);
                totalFree++;
            }
        }
        gettimeofday(&t1, 0);
        elapsed = (t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec;
        total += elapsed;
    }
    errCollect(0, 0, 0, 5, 1);
    average = total/100;
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total bytes requested: %d\n", totalBytes);
    printf("Total calls to free: %d\n", totalFree);
    printf("Total calls to free swapped to malloc: %d\n", totalSwap);
    printf("Average time of execution: %lf ms.\n", average);
    
    printf("\n\nTest E - (step bytes then free * 1000) * 100...\n\n");
    totalMalloc = 0, totalFree = 0, validMalloc = 0, total = 0;
    
    for(a1 = 0; a1 < 100; a1++){
        gettimeofday(&t0, 0);
        int countMalloc = 0, countNull = 0;
        for (a2 = 0; a2 < 1000; a2++){
            testE[a2] = (char*)malloc(a2*sizeof(char));//call malloc stepping in size with counter
            totalMalloc++;
            if(testE[a2] != NULL){//checks for valid call
                free(testE[a2]);//free
                totalFree++;
                validMalloc++;
            }
            else{
                countNull++;
            }
            totalBytes = totalBytes + a2;
        }
        validMalloc = validMalloc + countMalloc;
        gettimeofday(&t1, 0);
        elapsed = (t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec;
        total += elapsed;
    }
    errCollect(0, 0, 0, 5, 1);
    average = total/100;
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total valid calls to malloc: %d\n", validMalloc);
    printf("Total bytes requested: %d\n", totalBytes);
    printf("Total calls to free: %d\n", totalFree);
    printf("Average time of execution: %lf ms.\n", average);
    
    printf("\n\nTest F - (step byte malloc * 1000 then free * 1000) * 100...\n\n");
    totalMalloc = 0, totalFree = 0, validMalloc = 0, total = 0;
    
    for(a1 = 0; a1 < 100; a1++){
        gettimeofday(&t0, 0);
        int countMalloc = 0, countNull = 0;
        for (a2 = 1; a2 < 1001; a2++){
            testF[a2] = (char*)malloc(a2 * sizeof(char));
            totalMalloc++;
            if(testF[a2] != NULL)
            {
                countMalloc++;
            }
            else{
                countNull++;
            }
        }
        for (a3 = countMalloc; a3 >= 1; a3--){
            free(testF[a3]);
            totalFree++;
        }
        validMalloc = validMalloc + countMalloc;
        gettimeofday(&t1, 0);
        elapsed = (t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec;
        total += elapsed;
    }
    errCollect(0, 0, 0, 5, 1);
    average = total/100;
    printf("\nTotal calls to malloc: %d\n", totalMalloc);
    printf("Total valid calls to malloc: %d\n", validMalloc);
    printf("Total calls to free: %d\n", totalFree);
    printf("Average time of execution: %lf ms.\n", average);
    
    return 0;  
}
