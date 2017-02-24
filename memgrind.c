#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "mymalloc.h"

int main(int argc, char *argv[]){

    int a1 = 0;
    int a2 = 0;
    int a3 = 0;
    //int * testA;
    int aMallocTotal = 0;
    int aFreeTotal= 0;
    //double aTimeTotal = 0;
    int b1 = 0;
    int b2 = 0;
    int bMallocTotal = 0;
    int bFreeTotal= 0;
    int bTimeTotal = 0;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int c4 = 0;
    int cMallocTotal = 0;
    int cFreeTotal= 0;
    int cRandom = 0;
    int cTimeTotal = 0;
    int d1 = 0;
    int d2 = 0;
    int d3 = 0;
    int d4 = 0;
    int dMallocTotal = 0;
    int dFreeTotal= 0;
    int dRandomChoice = 0;
    int dRandomSize = 0;
    int dBytesTotal = 0;
    int dAllMTotal = 0;
    int dAllFTotal = 0;
    int dTimeTotal = 0;
    int e1 = 0;
    int e2 = 0;
    //int e3 = 0;
    int eMallocTotal = 0;
    int eFreeTotal= 0;
    int eTimeTotal = 0;
    int f1 = 0;
    int f2 = 0;
    //int f3 = 0;
    int fMallocTotal = 0;
    int fFreeTotal= 0;
    int fTimeTotal = 0;
    int testRuns = 99;
    int mallocRuns = 999;
    //time_t timer1;
    //time_t timer2;
    //struct timeval tv;
    
    printf("Test A: malloc x 1000 then free x 1000...\n");
    for (a1=0; a1 <= testRuns; a1++){
        //timer1 = time(NULL);
        for (a2=0; a2 <= mallocRuns; a2++){
            //testA = (int*)malloc(1);
            aMallocTotal++;
            printf("Added %d", a2);
        }
        for (a3=mallocRuns; a3 >= 0; a3--){
            //free(testA);
            aFreeTotal++;
        }
        //timer2 = time(NULL);
        //aTimeTotal = (aTimeTotal + difftime(timer2, timer1));
    } //Test a
    //aTimeTotal = aTimeTotal/100;
    printf("Total malloc calls: %d.  Total free calls: %d\n", aMallocTotal, aFreeTotal);
    //printf("Mean time for 100 executions: %d\n\n", aTimeTotal);
    
    printf("Test B: malloc then free x 1000...\n");
    for (b1=0; b1 <= testRuns; b1++){
        for (b2=0; b2 <= mallocRuns; b2++){
            //testA = (int*)malloc(1);
            bMallocTotal++;
            //free(testA);
            bFreeTotal++;
        }
        printf("------test %d\n", b1);
        //timer of total time take for each ieration of 100 test b
    }//Test b
    bTimeTotal = bTimeTotal/100;
    printf("Total malloc calls: %d.  Total free calls: %d\n", bMallocTotal, bFreeTotal);
    printf("Mean time for 100 executions: %d\n\n", bTimeTotal);
    
    printf("Test C: random 1 byte malloc or free x 1000...\n");
    for (c1=0; c1 <= testRuns; c1++){
        for (c2=0; c2 <= mallocRuns; c2++){
            cRandom = rand() % 100 + 1;
            if (cRandom <= 50){
            //malloc one bit
            cMallocTotal++;
            }
            else if (cRandom >=51){
                //if (){
                //check for memory existing, true = free
                //cFreeTotal++;
                //}
                //else if(){
                //If no memory to free, malloc one bit instead
                //cMallocTotal++;
                //}
            }
        }
        if (cFreeTotal < cMallocTotal){
            c4 = cMallocTotal - cFreeTotal;
            for (c3=c4; c3 > 0; c3--){
                //free remaining blocks
                cFreeTotal++;
            }
        }
        //timer of total time taken for each iteration of 100 test c
    }
    
    cTimeTotal = cTimeTotal/100;
    printf("Total malloc calls: %d.  Total free calls: %d\n", cMallocTotal, cFreeTotal);
    printf("Mean time for 100 executions: %d\n\n", cTimeTotal);
    
    printf("Test D: random 1-64 byte malloc or free last...\n");
    for (d1=0; d1 <= testRuns; d1++){
        dBytesTotal = 0;
        for (d2=0; d2 <= mallocRuns; d2++){
            dRandomChoice = rand() % 100 + 1;
            if (dRandomChoice <= 50){
                dRandomSize = rand() % 64 + 1;
                if (dBytesTotal + dRandomSize <= 1000){
                    //malloc dRandomSize
                    dBytesTotal = dBytesTotal + dRandomSize;
                    dMallocTotal++;
                }
                else{
                    //free last pointer
                    //dFreeTotal++
                }
            }
            else if(dRandomChoice >= 50){
                //if(){
                    //check for existing memory, true = free last block
                  //  dFreeTotal++;
                //}
                //else if(){
                    //no memory to free
                 //   dRandomSize = rand() % 64 + 1;
                    //malloc dRandomSize
                   // dBytesTotal = dBytesTotal + dRandomSize;
                    //dMallocTotal++;
                //}
            }
        dAllMTotal = dAllMTotal + dBytesTotal;
        }
        if (dFreeTotal < dMallocTotal){
            d4 = dMallocTotal - dFreeTotal;
            for (d3=d4; d3 >0 ; d3--){
                //free remaining blocks
                dFreeTotal++;
            }
        }
        //timer of total time taken for each iteration of 100 test d
    }
    dTimeTotal = dTimeTotal/100;
    printf("Total malloc calls: %d.  Total free calls: %d\n", dMallocTotal, dFreeTotal);
    printf("Total bytes assigned with malloc: %d\n", dAllMTotal);
    printf("Total bytes freed: %d\n", dAllFTotal);
    printf("Mean time for 100 executions: %d\n\n", dTimeTotal);
    
    printf("Test E: malloc and free in byte increments from 1-1000...\n");
    for (e1=0; e1 <= testRuns; e1++){
        for (e2=0; e2 <= mallocRuns; e2++){
        //assign malloc size of counter
            eMallocTotal++;
        //free size of counter
            eFreeTotal++;
        }
        //timer of total time taken for each iteration of 100 test a
    } //Test a
    eTimeTotal = eTimeTotal/100;
    printf("Total malloc calls: %d.  Total free calls: %d\n", eMallocTotal, eFreeTotal);
    printf("Mean time for 100 executions: %d\n\n", eTimeTotal);
    
    printf("Test F: ...\n");
    for (f1=0; f1 <= testRuns; f1++){
        for (f2=0; f2 <= mallocRuns; f2++){
        //assign malloc size of counter
            fMallocTotal++;
        //free size of counter
            fFreeTotal++;
        }
        //timer of total time taken for each iteration of 100 test a
    } //Test a
    fTimeTotal = fTimeTotal/100;
    printf("Total malloc calls: %d.  Total free calls: %d\n", fMallocTotal, fFreeTotal);
    printf("Mean time for 100 executions: %d\n\n", fTimeTotal);
    
    return 0;
}