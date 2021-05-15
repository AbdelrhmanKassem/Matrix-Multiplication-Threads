/*
 * first_method.c
 *
 *  Created on: 13 May 2021
 *      Author: abdelrhman
 */

#include "headers/first_method.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


extern long long **matA;
extern long long **matB;
extern long long **matOut;
extern long aRows;
extern long bRows;
extern long bColumns;


struct thread_data
{
   long	thread_id;
   long row;
   long column;
};


void *multiply_first_method(void *t);

//multiplication using only one thread
void first_method (){
	pthread_t thread[1];
	pthread_attr_t attr;
	int rc;

	/* Initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	long t=0;
	rc = pthread_create(&thread[0], &attr, multiply_first_method, (void *)t);
	if (rc) {
		printf("ERROR Creating Threads\n");
		exit(1);
	}


	/* Free attribute and wait for the thread */
	pthread_attr_destroy(&attr);
	rc = pthread_join(thread[0], NULL);
	if (rc) {
		printf("ERROR Joining Threads\n");
		exit(1);
	}


}

//multiplication function executed by the thread
void *multiply_first_method(void *threadarg){
	for(long i=0 ; i < aRows ; i++){
			for(long j=0 ; j < bColumns ; j++){
				//using temporary variable sum to avoid having to set the output matrix to zeros each time
				long long sum = 0;
				for(long k=0 ; k < bRows ; k++){
					sum += matA[i][k] * matB[k][j];
				}
				matOut[i][j] = sum;
			}
	}
	pthread_exit(NULL);
}



