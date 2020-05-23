// Cpp demo on the flaw of semaphore over mutex.
// Semaphores can be accessed and modified by any thread.
// It being just a signalling mechanism, so it can be modified by
// anythread during execution and can only work as a lock when implemented correctly.

//Only when the thread[i] finished should displaythread be called
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
sem_t mutex;
struct threaddetail
{
	int sum;
	int limit;
};
void* displaylimit(void* arg)
{
	/**/
}
void *mythread(void *arg)
{
	int sum = 0;
	threaddetail *cthread  = ((threaddetail *)arg);
	for(int i =0 ;i<cthread->limit;i++)
	{
		sum+=i;
		sleep(2);
	}
	cthread->sum = sum;
	pthread_exit(0);

}

int main(int argc , char** argv)
{
	if(argc < 2)
	{
		cout << " More than two arguments are required \n";
		exit(-1);
	}
	int threadcount  = argc -1; // print argc to see the value
	int threadlimit; // clarificiation on argv
	struct threaddetail currthread[threadcount];
	pthread_t tid[threadcount];
	for(int i = 0; i< threadcount ; i++)
	{
		threadlimit = atoi(argv[i+1]);
		currthread[i].limit = threadlimit;
		pthread_create(&tid[i],NULL ,mythread , (void*)&currthread[i]);
	}
	
	for(int i = 0; i< threadcount ; i++)
	{
		pthread_join(tid[i], NULL);
		cout <<"Thread " << i << "sum is " << currthread[i].sum <<endl;

	}

}
