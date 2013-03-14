
/* thread_mutex.c */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUMBER		3
#define REPEAT_NUMBER		3
#define DELAY_TIME_LEVELS	500.0

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;
void * thrd_func(void *arg)
{
	int thrd_num = (int)arg;
	int delay_time = 0, count = 0;
	int res;
	
	printf("Thread %d is starting\n", thrd_num);

	res = pthread_mutex_lock(&mutex);	
	if (res)
	{
		printf("Thread %d lock failed\n", thrd_num);	
		pthread_exit(NULL);
	}
		
	for (count = 0; count < REPEAT_NUMBER; count++)
	{
		
		delay_time = (int)(rand() * DELAY_TIME_LEVELS/(RAND_MAX)) + 1;
		usleep(delay_time * 1000);
		printf("\tThread %d: job %d delay = %d\n", thrd_num, count, delay_time);
	}

	printf("Thread %d finished\n", thrd_num);
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thread[THREAD_NUMBER];
	int no = 0, res;
	void * thrd_ret;
	
	srand(time(NULL));
	
	pthread_mutex_init(&mutex, NULL);
	for (no = 0; no < THREAD_NUMBER; no++)
	{
		res = pthread_create(&thread[no], NULL, thrd_func, (void*)no);
		if (res != 0)
		{
			printf("Create thread %d failed\n", no);
			exit(res);
		}

		pthread_detach(thread[no]);
	}
	
	printf("Create %d treads success\n"
			"###press enter to exit...\n", no);
	getchar();

	pthread_mutex_destroy(&mutex);	
	return 0;        
}
