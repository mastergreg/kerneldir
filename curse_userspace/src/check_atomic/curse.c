#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


#ifdef __i386__
# define __NR_curse 341
#else
# define __NR_curse 303
#endif

long curse (int command, int curse, pid_t target)
{
	return syscall(__NR_curse, command, curse, target);
}
