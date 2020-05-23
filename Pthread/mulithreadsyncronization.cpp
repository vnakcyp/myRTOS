// Cpp demo on the flaw of semaphore over mutex.
// Semaphores can be accessed and modified by any thread.
// It being just a signalling mechanism, so it can be modified by
// anythread during execution and can only work as a lock when implemented correctly.

//Only when the thread[i] finished should displaythread be called
//we can use mutex and binary semaphore interchangebly here.
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <semaphore.h>


using namespace std;
pthread_mutex_t mutex;
sem_t sempt;
struct threaddetail
{
	int sum;
	int limit;
	int tid;
};
void* displaylimit(void* arg)
{
	/*a semaphore to signal the completion of mythread so thta displaylimit starts
	 * using it*/
	//pthread_mutex_lock(&mutex);
	sem_wait(&sempt);
	threaddetail *cthread  = ((threaddetail *)arg);
	//sleep(2);
	cout << " output of thread "<<cthread->tid << "is " << cthread->sum << endl;

	//pthread_mutex_unlock(&mutex);
	sem_post(&sempt);
	pthread_exit(0);

	return NULL;
}
void* mythread(void *arg)
{
	//pthread_mutex_lock(&mutex);
	sem_wait(&sempt);
	int sum = 0;
	threaddetail *cthread  = ((threaddetail *)arg);
	cout << "Entering thread : " << cthread->tid <<"\n";

	for(int i =0 ;i<cthread->limit;i++)
	{
		sum+=i;
		sleep(2);
	}
	cthread->sum = sum;

	//pthread_mutex_unlock(&mutex);
	sem_post(&sempt);  // make sure to do this pthread_exit else the thread will never post the semaphore

	pthread_exit(0);
	return NULL;
}

int main(int argc , char** argv)
{
	if(argc < 2)
	{
		cout << " More than two arguments are required \n";
		exit(-1);
	}
	if(pthread_mutex_init(&mutex , NULL))
	{
		cout << "Mutex init failed \n";
		return 1;

	}
	sem_init(&sempt , 0 ,1);


	int threadcount  = argc -1; // print argc to see the value
	int threadlimit; // clarificiation on argv
	struct threaddetail currthread[threadcount];
	pthread_t tid1[threadcount];
	pthread_t tid2[threadcount];
	for(int i = 0; i< threadcount ; i++)
	{
		threadlimit = atoi(argv[i+1]);
		currthread[i].limit = threadlimit;
		currthread[i].tid = i;
		pthread_create(&tid1[i],NULL ,mythread , (void*)&currthread[i]);
		pthread_create(&tid2[i], NULL ,displaylimit , (void*)&currthread[i]);
	}

	for(int i = 0; i< threadcount ; i++)
	{
		pthread_join(tid1[i], NULL);
		pthread_join(tid2[i], NULL);
		//cout <<"Thread " << i << "sum is " << currthread[i].sum <<endl;

	}
	pthread_mutex_destroy(&mutex);
	return 0 ;

}
