#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curse/curse.h>

int main (void) {
	pid_t mypeed = 0;

	printf("\nActivate random_oops: %d\n",		 curse(ACTIVATE, "random_oops", getpid(),0,NULL ));
	printf("\nCast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(),0, NULL));
fork_again:
	mypeed=fork();
	if (mypeed<0) 
		printf("Error forking.\n");
	else if (mypeed==0)
		exit(EXIT_SUCCESS);
	else
		goto fork_again;
	printf("\nLift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
	return 0;
}

