/* thread_sem.c */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*
 * Recognizing leaks
 * 		If you create a joinable thread but forget to join it, its
 * 	resources or private memory are always kept in the process
 * 	space and never reclaimed. Always join the joinable threads;
 * 	by not joining them, you risk serious memory leaks.
 *		For example, a thread on Red Hat Enterprise Linux (RHEL4),
 *	needs a 10MB stack, which means at least 10MB is leaked if you
 *	haven't joined it. Say you design a manager-worker mode program
 *	to process incoming requests. More and more worker threads need
 *	to be created, perform individual tasks, and then terminate.
 *	If they are joinable threads and you haven't called the pthread_join()
 *	to join them, each produced thread will leak a sizeable amount of
 *	memory (at least 10MB per stack) after its termination. The size
 *	of leaked memory continuously increases as more and more worker
 *	threads are created and terminated without being joined. Further,
 *	the process will fail to create any new threads since no memory is
 *	available for creating new ones.
 */

#define THREAD_NUMBER		250
#define REPEAT_NUMBER		30
#define DELAY_TIME_LEVELS	500.0

static sem_t sem;

void * thrd_func(void *arg) {
	int thrd_num = (int) arg;
	int delay_time = 0;
	int count = 0;

	printf("Thread %d is starting\n", thrd_num);

	for (count = 0; count < REPEAT_NUMBER; count++) {
		if(sem_wait(&sem) < 0) {
			perror("sem_wait");
			continue;
		}

		printf("\tThread %d\n", thrd_num);

		delay_time = (int) (rand() * DELAY_TIME_LEVELS / (RAND_MAX)) + 1;
		usleep(delay_time);

		//printf("\tThread %d: job %d delay = %d\n", thrd_num, count, delay_time);
	}

	printf("Thread %d finished\n", thrd_num);

	pthread_exit(NULL);
}

int main(void) {
	pthread_t thread[THREAD_NUMBER];
	int no = 0, res;
	void * thrd_ret;

	srand(time(NULL));

	sem_init(&sem, 0, 0);
	for (no = 0; no < THREAD_NUMBER; no++) {

		res = pthread_create(&thread[no], NULL, thrd_func, (void*) no);
		if (res != 0) {
			perror("pthread_create");
			printf("Create thread %d failed\n", no);
			exit(res);
		}
		pthread_detach(thread[no]);
		usleep(1000);
	}

	printf("Create [%d] treads success. start to sem_post...\n", THREAD_NUMBER);

	int i;
	for (i = 0; i < THREAD_NUMBER*10; i++) {
		sem_post(&sem);
		usleep(1000);
	}

	sem_destroy(&sem);
	return 0;
}
