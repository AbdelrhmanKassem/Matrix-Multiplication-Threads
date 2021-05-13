/*
 * third_method.c
 *
 *  Created on: 13 May 2021
 *      Author: abdelrhman
 */
#include "third_method.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


extern long long **matA;
extern long long **matB;
extern long long **matOut;
extern long aRows;
extern long aColumns;
extern long bColumns;


struct thread_data
{
   long	thread_id;
   long row;
   long column;
};


void *multiply_third_method(void *data);
void third_method (){
	pthread_t thread[aRows*bColumns];
	pthread_attr_t attr;
	int rc;

	/* Initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	long t=0;
	for(long i=0; i<aRows; i++) {
		for(long j=0; j<bColumns; j++){
			struct thread_data *data = (struct thread_data *) malloc(sizeof(struct thread_data));
			data->row = i;
			data->column = j;
			data->thread_id = t;
			rc = pthread_create(&thread[t], &attr, multiply_third_method, (void *)data);
			if (rc) {
				perror("ERROR Creating Threads");
				exit(1);
			}
			t++;
		}
	}

	/* Free attribute and wait for the other threads */
	pthread_attr_destroy(&attr);
	t=0;
	for(long i=0; i<aRows; i++) {
		for(long j=0; j<bColumns; j++){
			rc = pthread_join(thread[t], NULL);
			if (rc) {
				perror("ERROR Joining Threads");
				exit(1);
			}
			t++;
		}
	}
}

void *multiply_third_method(void *threadarg){
	struct thread_data *data = (struct thread_data *) threadarg;

	long tid;
	long row;
	long column;
	tid = (*data).thread_id;
	row = (*data).row;
	column = (*data).column;
	free(threadarg);
	long long sum = 0;
	for (long i = 0; i < aColumns; i++) {
		sum += matA[row][i] * matB[i][column];
	}
	matOut[row][column] = sum;

	pthread_exit(NULL);
}

