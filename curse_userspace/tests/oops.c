#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curse/curse.h>

int main (void) {
	pid_t mypeed = 0;

fork_again:
	mypeed=fork();
	if (mypeed<0) {
		printf("Error forking.\n");
	else if (mypeed==0)
		exit(EXIT_SUCCESS);
	else
		goto fork_again;
	return 0;
}

