#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main (int argc, char **argv) {
	pid_t parent_pid, fpid, fpid2;

/*  Fork, and check cross-process permission changes */
	parent_pid = getpid();
	printf("\nActivate random_oops: %d\n",		 curse(ACTIVATE, "random_oops", 0, 0, NULL));

	printf("\n\n\n...Forking...\n\n");
	fpid = fork();
	if (fpid < 0) {
		perror("Could not fork");	
		exit(1);
	}
	if (fpid == 0) {

		raise(SIGSTOP);
		printf("\n---------ONLY-SU-ACTIVE------------\n");
		printf("\nChild: Cast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(),0, NULL));
		printf("\nChild: Lift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
		printf("\nChild: Cast random_oops on parent: %d\n", curse(CAST, "random_oops", parent_pid, 0, NULL));
		printf("\nChild: Lift random_oops from parent: %d\n", curse(LIFT, "random_oops", parent_pid, 0, NULL));
		printf("\nChild: Restore SU ACTIVE permissions to self : %d\n", curse(CURSE_CTRL, "no_fs_cache", getpid(), SU_ACTIVE_PERM_ON,NULL));
		printf("\nChild: Remove SU ACTIVE permissions from parent : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_ACTIVE_PERM_OFF,NULL));
		printf("\nChild: Restore SU ACTIVE permissions to parent : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_ACTIVE_PERM_ON,NULL));
		printf("\n-------------------------------------\n");
		raise(SIGSTOP);


		printf("\n-------------NONE------------------\n");
		printf("\nChild: Cast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(),0, NULL));
		printf("\nChild: Lift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
		printf("\nChild: Cast random_oops on parent: %d\n", curse(CAST, "random_oops", parent_pid, 0, NULL));
		printf("\nChild: Lift random_oops from parent: %d\n", curse(LIFT, "random_oops", parent_pid, 0, NULL));
		printf("\nChild: Restore SU ACTIVE permissions to self : %d\n", curse(CURSE_CTRL, "no_fs_cache", getpid(), SU_ACTIVE_PERM_ON,NULL));
		printf("\nChild: Remove SU ACTIVE permissions from parent : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_ACTIVE_PERM_OFF,NULL));
		printf("\nChild: Restore SU ACTIVE permissions to parent : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_ACTIVE_PERM_ON,NULL));
		printf("\n-------------------------------------\n");
		raise(SIGSTOP);


		printf("\n-----------------ALL-------------------\n");
		printf("\nChild: Cast random_oops on self: %d\n", curse(CAST, "random_oops", getpid(),0, NULL));
		printf("\nChild: Lift random_oops from self: %d\n", curse(LIFT, "random_oops", getpid(),0, NULL));
		printf("\nChild: Cast random_oops on parent: %d\n", curse(CAST, "random_oops", parent_pid, 0, NULL));
		printf("\nChild: Lift random_oops from parent: %d\n", curse(LIFT, "random_oops", parent_pid, 0, NULL));
		printf("\nChild: Restore SU ACTIVE permissions to self : %d\n", curse(CURSE_CTRL, "no_fs_cache", getpid(), SU_ACTIVE_PERM_ON,NULL));
		printf("\nChild: Remove SU ACTIVE permissions from parent : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_ACTIVE_PERM_OFF,NULL));
		printf("\nChild: Restore SU ACTIVE permissions to parent : %d\n", curse(CURSE_CTRL, "no_fs_cache", parent_pid, SU_ACTIVE_PERM_ON,NULL));
		printf("\n-------------------------------------\n");

		exit(1);

	} else {
		waitpid(-1, NULL, WUNTRACED);
		printf("\n-------------------------------------\n");
		printf("\nParent: Remove SU PASSIVE permissions from child : %d\n", curse(CURSE_CTRL, "no_fs_cache", fpid, SU_PASSIVE_PERM_OFF,NULL));
		printf("\nParent: Remove USR PASSIVE permissions from child : %d\n", curse(CURSE_CTRL, "no_fs_cache", fpid, USR_PASSIVE_PERM_OFF,NULL));
		printf("\nParent: Cast random_oops on child: %d\n", curse(CAST, "random_oops", fpid, 0, NULL));
		printf("\nParent: Lift random_oops from child: %d\n", curse(LIFT, "random_oops", fpid, 0, NULL));
		printf("\n-------------------------------------\n");
		kill(fpid, SIGCONT);

		waitpid(-1, NULL, WUNTRACED);
		printf("\n-------------------------------------\n");
		printf("\nParent: Remove SU ACTIVE permissions from child : %d\n", curse(CURSE_CTRL, "no_fs_cache", fpid, SU_ACTIVE_PERM_OFF,NULL));
		printf("\nParent: Cast random_oops on child: %d\n", curse(CAST, "random_oops", fpid, 0, NULL));
		printf("\nParent: Lift random_oops from child: %d\n", curse(LIFT, "random_oops", fpid, 0, NULL));
		printf("\n-------------------------------------\n");
		kill(fpid, SIGCONT);
		
		waitpid(-1, NULL, WUNTRACED);
		printf("\n-------------------------------------\n");
		printf("\nParent: Restore SU PASSIVE permissions to child : %d\n", curse(CURSE_CTRL, "no_fs_cache", fpid, SU_PASSIVE_PERM_ON,NULL));
		printf("\nParent: Restore SU ACTIVE permissions to child : %d\n", curse(CURSE_CTRL, "no_fs_cache", fpid, SU_ACTIVE_PERM_ON,NULL));
		printf("\nParent: Cast random_oops on child: %d\n", curse(CAST, "random_oops", fpid, 0, NULL));
		printf("\nParent: Lift random_oops from child: %d\n", curse(LIFT, "random_oops", fpid, 0, NULL));
		printf("\n-------------------------------------\n");
		kill(fpid, SIGCONT);

		wait(fpid);
		printf("\nDeactivate random_oops: %d\n",		 curse(DEACTIVATE, "random_oops", parent_pid,0,NULL ));
	}
	return 0;
}
