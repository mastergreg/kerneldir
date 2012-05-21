#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <curse_imp/curse.h>

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
	
	//printf("%d\n", curse(98, 49, 24));		//Initial stub: outdated.
	printf("%d\n", curse(ACTIVATE, 0, 0));

//	printf("%d\n", curse(DEACTIVATE, 0, 0));

	return 0;
}
