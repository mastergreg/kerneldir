//#include <linkage.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __i386__
#define __NR_curse 341
#else
#define __NR_curse 303
#endif

long curse (char *opa) {
	return syscall(__NR_curse, 10, 0, 0, 0, opa);
}

//Testing inode from path.
int main (int argc, char *argv[]) {
	int i;

	for (i=0; i<argc; i++)
		curse(argv[i]);

	return 0;
}
