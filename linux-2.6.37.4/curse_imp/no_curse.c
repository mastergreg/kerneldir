#include <linux/syscalls.h>
//#include <asm/current.h>

#include <curse/no_curse.h>
#include <curse/curse.h>

void no_curse_init (void) {
	struct task_curse_struct *cur_curse;
	unsigned long irqflags;

	printk(KERN_INFO "no_curse: in init");
	cur_curse = &(current->curse_data);

	spin_lock_irqsave(&((cur_curse)->protection), irqflags);
	// No need to check if curse is active
	//Making the process unable to cast a curse is done by masking it s active permissions.
	cur_curse->permissions &= ~(_USR_ACTIVE_PERM | _SU_PASSIVE_PERM);
	printk(KERN_INFO "no_curse: initialized with permissions %d", cur_curse->permissions);
	spin_unlock_irqrestore(&((cur_curse)->protection), irqflags);
	return;
}

void no_curse_inject (uint64_t mask) {

	printk(KERN_INFO "no_curse: in inject");
	/*
	struct task_curse_struct *cur_curse;
	unsigned long irqflags;

	cur_curse = &(current->curse_data);

	spin_lock_irqsave(&((cur_curse)->protection), irqflags);
	if (cur_curse->curse_field & mask) {	//The mask is the mask of the current curse.
		//Making the process unable to cast a curse is done by masking it s active permissions.
		cur_curse->permissions &= (_USR_ACTIVE_PERM|_GRP_ACTIVE_PERM|_SU_ACTIVE_PERM);
	}
	spin_unlock_irqrestore(&((cur_curse)->protection), irqflags);
	*/

	return;
}

void no_curse_destroy (void) {
	struct task_curse_struct *cur_curse;
	unsigned long irqflags;

	printk(KERN_INFO "no_curse: in destroy");
	cur_curse = &(current->curse_data);

	spin_lock_irqsave(&((cur_curse)->protection), irqflags);
	// FIXME: security exploit, process may gain permissions
	cur_curse->permissions &= (_USR_ACTIVE_PERM | _SU_ACTIVE_PERM);
	printk(KERN_INFO "no_curse: destroyed with permissions %d", cur_curse->permissions);
	spin_unlock_irqrestore(&((cur_curse)->protection), irqflags);
	return;
}
