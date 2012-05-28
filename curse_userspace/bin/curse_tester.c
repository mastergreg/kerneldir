#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv) {
	

	//printf("Blob: %d\n", curse(98, 49, 24));		//Initial stub: outdated.
	if (argc == 1) {
		exit(0);
	}
	pid_t pid;
	sscanf(argv[1], "%d", &pid);
	printf("\nActivate:\n\t%d\n", curse(ACTIVATE, "2", pid));
	//printf("\nCheck tainted:\n\t%d\n", curse(CHECK_TAINTED_PROCESS, 2, pid));
	//printf("\nCheck activity:\n\t%d\n", curse(CHECK_CURSE_ACTIVITY, 2, pid));
	printf("\nCast:\n\t%d\n", curse(CAST, "2", pid));
	printf("\nCheck tainted:\n\t%d\n", curse(CHECK_TAINTED_PROCESS, "2", pid));
	printf("\nCheck activity:\n\t%d\n", curse(CHECK_CURSE_ACTIVITY, "2", pid));
	//printf("\nLift:%d\n", curse(LIFT, 2, pid));
	printf("\nCheck tainted: %d\n", curse(CHECK_TAINTED_PROCESS, "2", pid));
	printf("\nCheck activity: %d\n", curse(CHECK_CURSE_ACTIVITY, "2", pid));
	//printf("\nDeactivate: %d\n", curse(DEACTIVATE, 2, pid));
	//printf("\nList: %d\n", curse(LIST_ALL, 2, pid));
	return 0;
}
