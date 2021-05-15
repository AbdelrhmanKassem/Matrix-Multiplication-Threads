/*
 * write_output.c
 *
 *  Created on: 12 May 2021
 *      Author: abdelrhman
 */
#include "headers/write_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

extern long long **matOut;
extern char* matOutFName;
extern long aRows;
extern long bColumns;
extern FILE *matOutFile;

//write the output matrix to the provided file along side the required information
void write_output(int NumberOfThreads ,struct timeval stop,struct  timeval start,int methodNo){

    matOutFile=fopen(matOutFName, "a");
    if(matOutFile==NULL){
        perror("Couldn't Open Files");
        exit(1);
    }
    else{
        fprintf(matOutFile , "Method %d Output\n",methodNo);
        fprintf(matOutFile , "Number of threads used: %d\n" , NumberOfThreads);
        long seconds = (stop.tv_sec - start.tv_sec);
        long micros = ((seconds * 1000000) + stop.tv_usec) - (start.tv_usec);
        fprintf(matOutFile,"Seconds taken %lu\n", seconds);;
        fprintf(matOutFile,"Total Microseconds taken: %lu\n", micros);
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


