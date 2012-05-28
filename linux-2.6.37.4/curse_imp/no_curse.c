#include <linux/syscalls.h>

#include <curse/no_curse.h>

void no_curse_inject (void) {
/*
	struct curse_struct *cur_curse;
	unsigned long irqflags;

	cur_curse = current->curse_data;

	spin_lock_irqsave(&((cur_curse).protection), irqflags);
	//We should change return type of inject to _Bool (int), and add defer argument in trigger.
	//Inject should take an argument ( the mask of the id as an argument ), for such cases.
	if (cur_curse.triggered & ***MASK GOES HERE***)
		***RETURN GOES HERE***
	spin_lock_irqrstore(&((cur_curse).protection), irqflags);
*/
	return;
}

