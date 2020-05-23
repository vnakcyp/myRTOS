// Cpp demo on the flaw of semaphore over mutex.
// Semaphores can be accessed and modified by any thread.
// It being just a signalling mechanism, so it can be modified by
// anythread during execution and can only work as a lock when implemented correctly.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;


void* thread1(void* arg)
{

	int myval = *((int*)arg);
	printf("Entering thread1 .. \n");
	sem_wait(&mutex);
	printf("\nEntered..\n");

	//critical section
	sleep(4);
	printf("I am from thread : %d" ,myval );

	//signal
	printf("\nJust Exiting...\n");
	sem_post(&mutex);
}
void* thread2(void* arg)
{
	int myval = *((int *)arg);
	printf("Entering thread2 .. \n");
	sem_post(&mutex);
	sem_wait(&mutex);
	printf("\nEntered ..\n");

	//critical section
	printf("I am working on thread 2 \n");
	printf("I am from thread : %d" ,myval );

	//signal
	printf("\nJust Exiting...\n");
	sem_post(&mutex);

}


int main()
{
	sem_init(&mutex, 0, 1);
	pthread_t t1,t2;
	int thread_1  = 1;
	int thread_2 = 2;
	pthread_create(&t1,NULL,thread1,(void*)&thread_1);
	sleep(2);
	pthread_create(&t2,NULL,thread2,(void*)&thread_2);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&mutex);
	return 0;
}
