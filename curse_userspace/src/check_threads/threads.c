#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <pthread.h>

void *it_is_fun(void *ptr)
{
	struct curse_list_entry cleo[10];
	printf("I am thread num %d, and i call u curse!\n", (int )ptr);
	curse(LIST_ALL, 0, 0, 0, cleo);
	printf("I am thread num %d, and i just finished!\n", (int) ptr);
}


int main (int argc, char **argv)
{

	pthread_t thread1, thread2;
	int ret1,ret2;


	ret1 = pthread_create(&thread1, NULL, it_is_fun, (void *) 1);
	ret2 = pthread_create(&thread2, NULL, it_is_fun, (void *) 2);

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	printf("Thread 1 returns: %d\n", ret1);
	printf("Thread 2 returns: %d\n", ret2);

	return 0;
}
