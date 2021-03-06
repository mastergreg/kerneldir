#ifdef CONFIG_CURSES
#ifdef CONFIG_NO_CURSE
#include <linux/syscalls.h>
//#include <asm/current.h>

#include <curse/no_curse.h>
#include <curse/curse.h>
#include <curse/curse_externals.h>

void no_curse_init (struct task_struct *target)
{ 
	curse_trigger(1, 0xBEA7CE5C);
	return;
}

void no_curse_inject (uint64_t mask)
{
	struct task_curse_struct *cur_curse;
	unsigned long irqflags;

	cur_curse = &(current->curse_data);

	spin_lock_irqsave(&((cur_curse)->protection), irqflags);
	cur_curse->permissions &= ~(_USR_ACTIVE_PERM | _SU_ACTIVE_PERM);
	spin_unlock_irqrestore(&((cur_curse)->protection), irqflags);

	return;
} 

void no_curse_destroy (struct task_struct *target)
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

#endif	/* CONFIG_NO_CURSE */
#endif	/* CONFIG_CURSES */
