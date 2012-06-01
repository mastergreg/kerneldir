#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main (int argc, char **argv) {
	pid_t parent_pid, fpid, fpid2;

/* Scenario : Cast random_oops and no_fs_cache on self, fork two levels, and check if tainted*/
	parent_pid = getpid();
	printf("\nActivate random_oops: %d\n",		 curse(ACTIVATE, "random_oops", parent_pid,0,NULL ));
	printf("\nActivate no_fs_cache: %d\n",		 curse(ACTIVATE, "no_fs_cache", parent_pid,0,NULL ));
	printf("\nCheck if self is tainted by random_oops: %d\n",		 curse(CHECK_TAINTED_PROCESS, "random_oops", parent_pid,0,NULL ));
	printf("\nCheck if self is tainted by no_curse: %d\n",		 curse(CHECK_TAINTED_PROCESS, "no_curse", parent_pid,0,NULL ));
	printf("\nCheck if self is tainted by no_fs_cache: %d\n",		 curse(CHECK_TAINTED_PROCESS, "no_fs_cache", parent_pid,0,NULL ));
	// Inheritance Check
	printf("\nCast random_oops on self: %d\n", curse(CAST, "random_oops", parent_pid,0, NULL));
	printf("\nRemove inheritance from no_fs_cache: %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, INH_OFF,NULL));
	printf("\nCast no_fs_cache on self: %d\n", curse(CAST, "no_fs_cache", parent_pid,0, NULL));

	printf("\n\n\n...Forking...\n\n");
	fpid = fork();
	if (fpid < 0) {
		perror("Could not fork");
		exit(1);
	}
	if (fpid == 0) {
		printf("\n\n\n...Forking...\n\n");
		fpid2 = fork();
		if (fpid2 < 0) {
			perror("Could not fork2");
			exit(1);
		}
		if (fpid2 == 0) {
			/* Second Child */
			printf("\nChild2: Check if self is tainted by random_oops: %d\n",		 curse(CHECK_TAINTED_PROCESS, "random_oops", getpid(),0,NULL ));
			printf("\nChild2: Check if self is tainted by no_fs_cache: %d\n",		 curse(CHECK_TAINTED_PROCESS, "no_fs_cache", getpid(),0,NULL ));
			exit(0);
		} else {
			/* First Child */
			printf("\nChild: Check if self is tainted by random_oops: %d\n",		 curse(CHECK_TAINTED_PROCESS, "random_oops", getpid(),0,NULL ));
			printf("\nChild: Check if self is tainted by no_fs_cache: %d\n",		 curse(CHECK_TAINTED_PROCESS, "no_fs_cache", getpid(),0,NULL ));
			wait(fpid2);
			exit(0);
		}
	} else {
		wait(fpid);
		printf("\nDeactivate random_oops: %d\n",		 curse(DEACTIVATE, "random_oops", parent_pid,0,NULL ));
		printf("\nReset inheritance to no_fs_cache: %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, INH_ON,NULL));
		printf("\nDeactivate no_fs_cache: %d\n",		 curse(DEACTIVATE, "no_fs_cache", parent_pid,0,NULL ));
	}

	return 0;
}
