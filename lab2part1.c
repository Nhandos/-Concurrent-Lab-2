/* File:      lab2part1.c
 * Purpose:   Estimate pi using pthreads and monte carlo method
 * 
 * Compile:   gcc ...
 *	         needs my_rand.c, my_rand.h
 * Run:       ./lab2part1 <number of threads> <number of tosses>
 * Input:     None
 * Output:    Estimate of pi
 *
 * Note:      The estimated value of pi depends on both the number of threads and the number of "tosses".  
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_rand.h"


/* Global variables */
int thread_count;
long long int number_in_circle = 0;
long long int number_of_tosses;

/* mutex */
pthread_mutex_t mutex;

/* Serial function */
void Get_args(int argc, char* argv[]);

/* Parallel function */
void *Thread_work(void* rank);

/*---------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	long i;
	pthread_t* thread_handles;
	double pi_estimate;
	
	Get_args(argc, argv);
	
	thread_handles = malloc(thread_count*sizeof(pthread_t));
	pthread_mutex_init(&mutex, NULL);
	
	
	for(i = 0; i < thread_count; i++) {
		pthread_create(&thread_handles[i], NULL, &Thread_work, i);
	}
		
	for(i = 0; i < thread_count; i++) {
		pthread_join(thread_handles[i], NULL);
	}
	
	pi_estimate = 4*number_in_circle/((double) number_of_tosses);
	printf("Estimated pi: %e\n", pi_estimate);

	pthread_mutex_destroy(&mutex);
	return 0;
}

/*---------------------------------------------------------------------
 * Function:		Thread_work 
 * Purpose:		Calculate number in circle using monte carlo method
 * In arg:		rank
 * Global in vars:	number_of_tosses, thread_count
 * Global out vars:	number_in_circle
 */

void *Thread_work(void* rank) {
	long my_rank = (long) rank;
	long long int toss;
	long long int local_number_in_circle = 0;
	long long int local_tosses = number_of_tosses/thread_count;
	long long int start = local_tosses*my_rank;
	long long int finish = start+local_tosses;
	double x, y, distance_squared;
        unsigned seed = my_rank+1;  /* must be nonzero */

#ifdef DEBUG
	printf("Rank: %ld, start = %lld, finish = %lld\n", rank, start, finish);
#endif
	
	srand(seed);
	for(toss = start; toss < finish; toss++) {
		x = (double) rand() / RAND_MAX * 2 - 1;
		y = (double) rand() / RAND_MAX * 2 - 1;
		distance_squared = x*x + y*y;
		if (distance_squared <= 1)
			local_number_in_circle += 1;
	}

#ifdef DEBUG
	printf("%ld: # In circle = %lld\n", my_rank, local_number_in_circle);
#endif

	pthread_mutex_lock(&mutex);
	number_in_circle += local_number_in_circle;
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}



/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argc, argv
 * Globals out: thread_count, n
 */

void Get_args(int argc, char* argv[]) {
	thread_count = strtol(argv[1], NULL, 10);  
	number_of_tosses = strtoll(argv[2], NULL, 10);
}  /* Get_args */

