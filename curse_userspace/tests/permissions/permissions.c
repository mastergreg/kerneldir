#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main (int argc, char **argv) {
	pid_t parent_pid, fpid, fpid2;

/* Scenario : Perform change, and see if you can curse on self*/
	parent_pid = getpid();
	printf("\nActivate random_oops: %d\n",		 curse(ACTIVATE, "random_oops", parent_pid,0,NULL ));
	printf("\nCheck if self is tainted by random_oops: %d\n",		 curse(CHECK_TAINTED_PROCESS, "random_oops", parent_pid,0,NULL ));
	printf("\nRemove permissions from this process: %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, USR_PERM_OFF,NULL));
	printf("\nRemove permissions from this process: %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_PERM_OFF,NULL));
	printf("\nCast random_oops on self: %d\n", curse(CAST, "random_oops", parent_pid,0, NULL));
	printf("\nLift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
	printf("\nReset permissions to process: %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, USR_PERM_ON,NULL));
	printf("\nRemove permissions from this process: %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_PERM_ON,NULL));
	printf("\nCast random_oops on self: %d\n", curse(CAST, "random_oops", parent_pid,0, NULL));
	printf("\nDeactivate random_oops: %d\n",		 curse(DEACTIVATE, "random_oops", parent_pid,0,NULL ));
	printf("\nCheck if self is tainted by random_oops: %d\n",		 curse(CHECK_TAINTED_PROCESS, "random_oops", parent_pid,0,NULL ));

	return 0;
}
