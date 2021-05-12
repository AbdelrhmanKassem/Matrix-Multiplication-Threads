/*
 * write_output.c
 *
 *  Created on: 12 May 2021
 *      Author: abdelrhman
 */
#include "write_output.h"
#include <stdio.h>
#include <sys/time.h>

extern long long **matOutM1;
extern long long **matOutM2;
extern long long **matOutM3;
extern char* matOutFName;
extern long aRows;
extern long bColumns;
extern FILE *matOutFile;

void write_output(int NumberOfThreads ,struct timeval stop,struct  timeval start,int methodNo){

    matOutFile=fopen(matOutFName, "a");
    if(matOutFile==NULL){
        perror("Couldn't Open Files");
        exit(1);
    }
    else{
        fprintf(matOutFile , "Method %d Output\n",methodNo);
        fprintf(matOutFile , "Number of threads used: %d\n" , NumberOfThreads);
        fprintf(matOutFile,"Seconds taken %lu\n", stop.tv_sec - start.tv_sec);;
        fprintf(matOutFile,"Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
        int i=0 , j=0;
        for(i ; i< aRows ; i++){
            j=0;
            for(j ; j<bColumns ; j++){
                    if(methodNo==1)
                        fprintf(matOutFile , "%lld  ", matOutM1[i][j]);
                    else if(methodNo==2)
                        fprintf(matOutFile , "%lld  ", matOutM2[i][j]);
                    else if(methodNo==3)
                        fprintf(matOutFile , "%lld  ", matOutM3[i][j]);

            }
        fprintf(matOutFile , "\n");
        }
        fclose(matOutFile);
    }
}


