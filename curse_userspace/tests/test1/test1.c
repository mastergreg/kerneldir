#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv) {
	pid_t parent_pid, fpid;

/* Scenario 1: After casting no_curse, no other curse should be cast by either parent or child */	
	parent_pid = getpid();

	printf("\nActivate : %d\n",		 curse_by_name3(ACTIVATE, "no_curse", parent_pid));
	printf("\nCast no_curse: %d\n",  curse_by_name3(CAST, "no_curse", parent_pid));
	
	fpid = fork();
	if (fpid < 0) {
		perror("Could not fork");
		exit(1);
	} 
	if (fpid == 0) {
		printf("\nCast no_fs_cache: %d\n", curse_by_name3(CAST, "no_fs_cache", parent_pid));
		printf("\nCast no_fs_cache: %d\n", curse_by_name3(CAST, "no_fs_cache", getpid()));
	} else {
		printf("\nCheck activity: %d\n", curse_by_name3(CHECK_CURSE_ACTIVITY, "no_curse", parent_pid));
	}

	printf("\nDeactivate: %d\n", 	 curse_by_name3(DEACTIVATE, "no_curse", parent_pid));

	return 0;
}
