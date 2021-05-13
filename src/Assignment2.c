/*
 ============================================================================
 Name        : Assignment2.c
 Author      : abdelrhman
 Version     :
 Copyright   :
 Description : Hello World in C, Ansi-style
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
#include <unistd.h>


char *matAFName;
char *matBFName;
char *matOutFName;
long aRows,aColumns,bRows,bColumns;
long long **matA;
long long **matB;;
long long **matOut;
extern long aRows;
extern long bColumns;
struct timeval stop, start;

int main(int argc , char** argv)
{
    if (argc==4){
        //user entered file names correctly
        matAFName = malloc (strlen (argv[1]) + 1);
        matBFName = malloc (strlen (argv[2]) + 1);
        matOutFName = malloc (strlen (argv[3]) + 1);
        strcpy(matAFName ,argv[1]);
        strcpy(matBFName ,argv[2]);
        strcpy(matOutFName ,argv[3]);
    }
    else{
        matAFName = malloc (strlen ("a.txt") + 1);
        matBFName = malloc (strlen ("b.txt") + 1);
        matOutFName = malloc (strlen ("c.txt") + 1);
        strcpy(matAFName ,"a.txt");
        strcpy(matBFName ,"b.txt");
        strcpy(matOutFName ,"c.txt");
    }




    printf("Reading files...\n");
    read_matrices();

    //first method
    gettimeofday(&start, NULL);
    first_method();
    sleep(1);
    gettimeofday(&stop, NULL);
    write_output(1,stop,start,1);
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);

    //second method
    gettimeofday(&start, NULL);
    second_method();
    sleep(2);
    gettimeofday(&stop, NULL);
    write_output(aRows,stop,start,2);
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);

    //third method
    gettimeofday(&start, NULL);
    third_method();
    sleep(3);
    gettimeofday(&stop, NULL);
    write_output(aRows*bColumns,stop,start,3);
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);

    printf("Multiplication Done.\nExiting...");
    exit(0);

}
