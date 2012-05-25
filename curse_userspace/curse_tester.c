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
	printf("Activate: %d\n", curse(ACTIVATE, 1, 1));
	printf("Check tainted: %d\n", curse(CHECK_TAINTED_PROCESS, 1, 1));
	printf("Check activity: %d\n", curse(CHECK_CURSE_ACTIVITY, 1, 1));
	printf("Cast: %d\n", curse(CAST, 1, 1));
	printf("Check tainted: %d\n", curse(CHECK_TAINTED_PROCESS, 1, 1));
	printf("Check activity: %d\n", curse(CHECK_CURSE_ACTIVITY, 1, 1));
	printf("Lift: %d\n", curse(LIFT, 1, 1));
	printf("Check tainted: %d\n", curse(CHECK_TAINTED_PROCESS, 1, 1));
	printf("Check activity: %d\n", curse(CHECK_CURSE_ACTIVITY, 1, 1));
	printf("Deactivate: %d\n", curse(DEACTIVATE, 1, 1));
	printf("List: %d\n", curse(LIST_ALL, 1, 1));

	printf("Activate: %d\n", curse(ACTIVATE, 1, 1172));
	return 0;
}