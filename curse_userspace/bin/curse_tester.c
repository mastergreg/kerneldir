#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv) {
	

	//printf("Blob: %d\n", curse(98, 49, no_fs_cache4));		//Initial stub: outdated.
	printf("\nActivate:\n\t%d\n", curse(ACTIVATE, "no_fs_cache", getpid(), 0, NULL));
	//printf("\nCheck tainted:\n\t%d\n", curse(CHECK_TAINTED_PROCESS, no_fs_cache, getpid()));
	//printf("\nCheck activity:\n\t%d\n", curse(CHECK_CURSE_ACTIVITY, no_fs_cache, getpid()));
	printf("\nCast:\n\t%d\n", curse(CAST, "no_fs_cache", getpid(), 0, NULL));
	printf("\nCheck tainted:\n\t%d\n", curse(CHECK_TAINTED_PROCESS, "no_fs_cache", getpid(), 0, NULL));
	printf("\nCheck activity:\n\t%d\n", curse(CHECK_CURSE_ACTIVITY, "no_fs_cache", getpid(), 0, NULL));
	//printf("\nLift:%d\n", curse(LIFT, no_fs_cache, getpid()));
	printf("\nCheck tainted: %d\n", curse(CHECK_TAINTED_PROCESS, "no_fs_cache", getpid(), 0, NULL));
	printf("\nCheck activity: %d\n", curse(CHECK_CURSE_ACTIVITY, "no_fs_cache", getpid(), 0, NULL));
	//printf("\nDeactivate: %d\n", curse(DEACTIVATE, no_fs_cache, getpid()));
	//printf("\nList: %d\n", curse(LIST_ALL, no_fs_cache, getpid()));
	return 0;
}
