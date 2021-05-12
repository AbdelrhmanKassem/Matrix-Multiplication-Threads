/*
 * write_output.c
 *
 *  Created on: 12 May 2021
 *      Author: abdelrhman
 */
#include "write_output.h"
#include <stdio.h>
#include <sys/time.h>

extern long long **matOut;
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
        for(int i=0 ; i<aRows ; i++){
            for(int j=0 ; j<bColumns ; j++){
            	fprintf(matOutFile , "%lld\t", matOut[i][j]);
            }
        fprintf(matOutFile , "\n");
        }
        fprintf(matOutFile , "\n\n\n");

        fclose(matOutFile);
    }
}


