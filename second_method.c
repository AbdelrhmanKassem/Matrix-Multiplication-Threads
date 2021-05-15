/*
 * second_method.c
 *
 *  Created on: 13 May 2021
 *      Author: abdelrhman
 */
#include "headers/second_method.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

extern long long **matA;
extern long long **matB;
extern long long **matOut;
extern long aRows;
extern long bRows;
extern long bColumns;


//struct to provide the row number to each thread
struct thread_data
{
   long	thread_id;
   long row;
};


void *multiply_second_method(void *data);

//multiply each row in a separate thread
void second_method (){
	pthread_t thread[aRows];
	pthread_attr_t attr;
	int rc;
	long t;

	/* Initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(t=0; t<aRows; t++) {
		struct thread_data *data = (struct thread_data *) malloc(sizeof(struct thread_data));
		data->row = t;
		data->thread_id = t;
		rc = pthread_create(&thread[t], &attr, multiply_second_method, (void *)data);
		if (rc) {
			printf("ERROR Creating Threads\n");
			exit(1);
		}
	}

	/* Free attribute and wait for the other threads */
	pthread_attr_destroy(&attr);
	for(t=0; t<aRows; t++) {
		rc = pthread_join(thread[t], NULL);
		if (rc) {
			printf("ERROR Joining Threads\n");
			exit(1);
		}
	}
}


//multiplication function executed by the thread
void *multiply_second_method(void *threadarg){
	struct thread_data *data = (struct thread_data *) threadarg;

	long row;
	row = (*data).row;
	free(threadarg);
	for(long i= 0 ; i < bColumns ; i++){
		long long sum=0;
		for(long j=0 ; j < bRows ; j++){
			sum += matA[row][j] * matB[j][i];
		}
		matOut[row][i] = sum;
	}
	pthread_exit(NULL);
}

