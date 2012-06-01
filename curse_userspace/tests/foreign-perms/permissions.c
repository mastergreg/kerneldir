#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main (int argc, char **argv) {
	pid_t parent_pid, fpid, fpid2;

/*  Fork, and check cross-process permission changes */
	parent_pid = getpid();
	printf("\nActivate random_oops: %d\n",		 curse(ACTIVATE, "random_oops", parent_pid,0,NULL ));
	printf("\nCheck if self is tainted by random_oops: %d\n",		 curse(CHECK_TAINTED_PROCESS, "random_oops", parent_pid,0,NULL ));

	printf("\n\n\n...Forking...\n\n");
	fpid = fork();
	if (fpid < 0) {
		perror("Could not fork");	
		exit(1);
	}
	if (fpid == 0) {
			printf("\nChild: Cast no_fs_cache on self: %d\n", curse(CAST, "no_fs_cache", getpid(),0, NULL));
			raise(SIGSTOP);
			printf("\nChild: Cast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(),0, NULL));
			raise(SIGSTOP);
			printf("\nChild: Restore USR permissions to parent : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, USR_PERM_ON,NULL));
			exit(1);
		} else {
			printf("\nParent: Remove SU permissions from child : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_PERM_OFF,NULL));
			waitpid(-1, NULL, WUNTRACED);
			kill(fpid, SIGCONT);
			printf("\nParent: Restore SU permissions to child : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_PERM_ON,NULL));
			printf("\nParent: Remove USR permissions from self : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, USR_PERM_OFF,NULL));
			waitpid(-1, NULL, WUNTRACED);
			kill(fpid, SIGCONT);
			printf("\nParent: Cast random_oops on child: %d\n", curse(CAST, "random_oops", fpid, 0, NULL));
			printf("\nParent: Lift random_oops from child: %d\n", curse(LIFT, "random_oops", fpid, 0, NULL));
			printf("\nParent: Cast random_oops on child: %d\n", curse(CAST, "random_oops", fpid, 0, NULL));
			printf("\nParent: Lift random_oops from child: %d\n", curse(LIFT, "random_oops", fpid, 0, NULL));
		}
	printf("\nDeactivate random_oops: %d\n",		 curse(DEACTIVATE, "random_oops", parent_pid,0,NULL ));
	return 0;
}
