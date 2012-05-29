#include <linux/syscalls.h>
#include <linux/random.h>

#include <curse/random_oops.h>

void random_oops_init (void) {
	return;
}

void random_oops_destroy (void) {
	return;
}

void random_oops_inject (uint64_t mask) {
	static int r=0;

	if ((r = get_random_int()) == 0) {
		r=0;
		*(int *)NULL=0;		//If 0 page is not mapped, then we oops.
		goto not_oopsed;
	} else {
		goto out;
	}
	
not_oopsed:
	/*Here we try harder to create a kernel oops.*/
	BUG();
out:
	return;
}

