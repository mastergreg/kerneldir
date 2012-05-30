//#include <linkage.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __i386__
#define __NR_curse 341
#else
#define __NR_curse 303
#endif

long curse () {
	return syscall(__NR_curse, 8,0,0,0,0);
}

int main (void) {
	curse();
	return 0;
}
