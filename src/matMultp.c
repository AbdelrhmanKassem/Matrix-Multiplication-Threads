/*
 ============================================================================
 Name        : Assignment2.c
 Author      : Abdelrhman
 Version     :
 Copyright   :
 Description : Matrix Multiplication Using thread main method
 ============================================================================
 */
#include "read_files.h"
#include "write_output.h"
#include "first_method.h"
#include "second_method.h"
#include "third_method.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>



char *matAFName;						//first matrix file name
char *matBFName;						//second matrix file name
char *matOutFName;						//output matrix file name
long long **matA;						//matrix A
long long **matB;						//matrix B
long long **matOut;						//output matrix
struct timeval stop, start;				//timeval structs for measuring execution time
extern long aRows,aColumns,bRows,bColumns;		//matrices dimensions

int main(int argc , char** argv)
{
    if (argc==4){			        //user entered file names correctly
    	//use the command line arguments provided
        matAFName = malloc (strlen (argv[1]) + 1);
        matBFName = malloc (strlen (argv[2]) + 1);
        matOutFName = malloc (strlen (argv[3]) + 1);
        strcpy(matAFName ,argv[1]);
        strcpy(matBFName ,argv[2]);
        strcpy(matOutFName ,argv[3]);
    }
    else{
    	//use the default file names
        matAFName = malloc (strlen ("a.txt") + 1);
        matBFName = malloc (strlen ("b.txt") + 1);
        matOutFName = malloc (strlen ("c.out") + 1);
        strcpy(matAFName ,"a.txt");
        strcpy(matBFName ,"b.txt");
        strcpy(matOutFName ,"c.out");
    }



    //reads the matrices from the files
    printf("Reading Matrices from \"%s\" and \"%s\"\n",matAFName,matBFName);
    read_matrices();

    //make sure we can actually multiply the matrices
    if(aColumns!=bRows){
    	perror("Invalid Matrices Dimensions");
    	exit(1);
    }


    printf("Writing results in \"%s\"\n\n",matOutFName);

    //first method
    gettimeofday(&start, NULL);
    first_method();
    gettimeofday(&stop, NULL);
    write_output(1,stop,start,1);			//write the output matrix to the file with the required information
    printf("Method 1:-\n");
    long seconds = (stop.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + stop.tv_usec) - (start.tv_usec);
    printf("Seconds taken %ld\n", seconds);
    printf("Total Microseconds taken: %ld\n\n\n", micros);

    //second method
    gettimeofday(&start, NULL);
    second_method();
    gettimeofday(&stop, NULL);
    write_output(aRows,stop,start,2);			//write the output matrix to the file with the required information
    printf("Method 2:-\n");
    seconds = (stop.tv_sec - start.tv_sec);
    micros = ((seconds * 1000000) + stop.tv_usec) - (start.tv_usec);
    printf("Seconds taken %ld\n", seconds);
    printf("Total Microseconds taken: %ld\n\n\n", micros);

    //third method
    gettimeofday(&start, NULL);
    third_method();
    gettimeofday(&stop, NULL);
    write_output(aRows*bColumns,stop,start,3);	//write the output matrix to the file with the required information
    printf("Method 3:-\n");
    seconds = (stop.tv_sec - start.tv_sec);
    micros = ((seconds * 1000000) + stop.tv_usec) - (start.tv_usec);
    printf("Seconds taken %ld\n", seconds);
    printf("Total Microseconds taken: %ld\n\n\n", micros);


    printf("Multiplication Done.\nExiting...");
    exit(0);

}
