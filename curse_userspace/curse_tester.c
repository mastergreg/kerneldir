#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <curse/curse.h>

#ifdef __i386__
# define __NR_curse 341
#else
# define __NR_curse 303 
#endif

long curse (int command, int curse, pid_t target) {
	return syscall(__NR_curse, command, curse, target);
}
/*Tutorial has a semicolon after the closing bracket of mycall(). Due to age?*/

int main (void) {
	
	//printf("Blob: %d\n", curse(98, 49, 24));		//Initial stub: outdated.
	printf("\nActivate:\n\t%d\n", curse(ACTIVATE, 1, 1));
	printf("\nCheck tainted:\n\t%d\n", curse(CHECK_TAINTED_PROCESS, 1, 1));
	printf("\nCheck activity:\n\t%d\n", curse(CHECK_CURSE_ACTIVITY, 1, 1));
	printf("\nCast:\n\t%d\n", curse(CAST, 1, 1));
	printf("\nCheck tainted:\n\t%d\n", curse(CHECK_TAINTED_PROCESS, 1, 1));
	printf("\nCheck activity:\n\t%d\n", curse(CHECK_CURSE_ACTIVITY, 1, 1));
	printf("\nLift:%d\n", curse(LIFT, 1, 1));
	printf("\nCheck tainted: %d\n", curse(CHECK_TAINTED_PROCESS, 1, 1));
	printf("\nCheck activity: %d\n", curse(CHECK_CURSE_ACTIVITY, 1, 1));
	printf("\nDeactivate: %d\n", curse(DEACTIVATE, 1, 1));
	printf("\nList: %d\n", curse(LIST_ALL, 1, 1));
	printf("\nActivate: %d\n", curse(ACTIVATE, 1, 1172));
	return 0;
}
