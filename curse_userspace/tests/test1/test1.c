#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv) {
	pid_t parent_pid, fpid;

/* Scenario 1: After casting no_curse, no other curse should be cast by either parent or child */	
	parent_pid = getpid();

	printf("\nActivate no_curse: %d\n",		 curse(ACTIVATE, "no_curse", parent_pid,0,NULL ));
	printf("\nCast random_oops on self: %d\n", curse(CAST, "random_oops", parent_pid,0, NULL));
	printf("\nActivate random_oops: %d\n",		 curse(ACTIVATE, "random_oops", parent_pid,0,NULL ));
	printf("\nCast random_oops on self: %d\n", curse(CAST, "random_oops", parent_pid,0, NULL));
	printf("\nLift random_oops from self: %d\n", curse(LIFT, "random_oops", parent_pid,0, NULL));
	printf("\n\n\n...Forking...\n\n");
	
	fpid = fork();
	if (fpid < 0) {
		perror("Could not fork");
		exit(1);
	} 
	if (fpid == 0) {
		printf("\nChild: Cast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(), 0 ,NULL));
		printf("\nChild: Lift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
		printf("\nChild: Cast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(), 0 ,NULL));
		printf("\nChild: Lift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
		printf("\nChild: Deactivate no_curse: %d\n", 	 curse(DEACTIVATE, "no_curse", getpid(), 0, NULL ));
		printf("\nChild: Cast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(), 0 ,NULL));
		printf("\nChild: Lift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
	} else {
		printf("\nParent: Cast no_curse on child: %d\n", curse(CAST, "no_curse", fpid,0, NULL));
		printf("\nParent: Cast random_oops on self: %d\n", curse(CAST, "random_oops", parent_pid, 0 ,NULL));
		printf("\nParent: Lift random_oops from self: %d\n", curse(LIFT, "random_oops", parent_pid,0, NULL));
		printf("\nParent: Lift no_curse: %d\n",  curse(LIFT, "no_curse", fpid, 0, NULL));
		printf("\nParent: Deactivate no_curse: %d\n", 	 curse(DEACTIVATE, "no_curse", parent_pid, 0, NULL ));
		printf("\nParent: Deactivate random_oops: %d\n", 	 curse(DEACTIVATE, "random_oops", parent_pid, 0, NULL ));
	}

	printf("\nAll: Cast no_curse on self: %d\n", curse(CAST, "no_curse", parent_pid,0, NULL));

	return 0;
}
