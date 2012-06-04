#ifdef CONFIG_CURSES
#include <linux/syscalls.h>
//#include <asm/current.h>

#include <curse/no_curse.h>
#include <curse/curse.h>

void no_curse_init (struct task_struct * target)
{
	struct task_curse_struct *tar_curse;
	unsigned long irqflags;

	tar_curse = &(target->curse_data);

	spin_lock_irqsave(&((tar_curse)->protection), irqflags);
	// No need to check if curse is active
	//Making the process unable to cast a curse is done by masking it s active permissions.
	tar_curse->permissions &= ~(_USR_ACTIVE_PERM | _SU_PASSIVE_PERM);
	spin_unlock_irqrestore(&((tar_curse)->protection), irqflags);
	return;
}

void no_curse_inject (uint64_t mask)
{

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

void no_curse_destroy (struct task_struct * target)
{
	struct task_curse_struct *tar_curse;
	unsigned long irqflags;

	tar_curse = &(target->curse_data);

	spin_lock_irqsave(&((tar_curse)->protection), irqflags);
	// FIXME: security exploit, process may gain permissions
	tar_curse->permissions |= (_USR_ACTIVE_PERM | _SU_ACTIVE_PERM);
	spin_unlock_irqrestore(&((tar_curse)->protection), irqflags);
	return;
}
#endif /* CONFIG_CURSES */
