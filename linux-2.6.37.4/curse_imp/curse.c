/*
 * This file contains the source code for the curse system call.
 * 
 * [The functions used by the system call are declared prior to the call source and sourced below it.]
 *
 */
 
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/types.h>		/*Sentinels prevent multiple inclusion.*/
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <asm/atomic.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/proc_fs.h>
#include <linux/rcupdate.h>

#include <curse/curse.h>
#include <curse/curse_types.h>

//External declarations.
extern int max_curse_no;

//Other functions.
/*This function returns the index of the element with the specified curse id (or to the sentinel if invalid).*/
inline int index_from_no (curse_id_t a_c_id) {
    int i = ((a_c_id < max_curse_no) ? a_c_id : max_curse_no);
	return i;
}

/*This function returns the bitmask for the specified curse id.*/
inline uint64_t bitmask_from_no (curse_id_t a_c_id) {
	return curse_list_pointer[index_from_no(a_c_id)].curse_bit;
}

/*This function checks if current is allowed to change the state of the target proc.*/
inline int check_permissions (curse_id_t curse_no, pid_t target) {
	struct task_struct *foreign_task;
	const struct cred *foreign_c, *local_c;
	struct syscurse * current_curse;
	uint64_t current_perms;
	int ret;

	ret = -ESRCH;		//FIXME: Sanity check.
	rcu_read_lock();
	foreign_task = find_task_by_vpid(target);
	rcu_read_unlock();
	if (!foreign_task)
		goto out;
	ret = -EINVAL;		//FIXME: Sanity check.
	foreign_c = get_task_cred(foreign_task);
	if (!foreign_c)
		goto out_with_foreign;

	local_c = get_current_cred();
	/* am i root or sudo?? */
	/* do we belong to the same effective user?*/
	/* or the same group? */

	/* FIXME: ale1ster said sth about a wrapper, this is just temporary */
	current_curse = &curse_list_pointer[index_from_no(curse_no)];
	current_perms = current_curse->permissions;


	ret = (((local_c->euid == 0) && (current_perms & _S_M))													|| \
		(((local_c->euid == foreign_c->euid) || (local_c->euid == foreign_c->uid)) && (current_perms & _U_M))	||	\
		((local_c->gid == foreign_c->gid) && (current_perms & _G_M)));			//su, user, group

	printk(KERN_INFO "perm ret =%d\n", ret);
//out_with_local:
	put_cred(local_c);
out_with_foreign:
	put_cred(foreign_c);
out:
	return ret;
}

/*This is the system call source base function.*/
SYSCALL_DEFINE3(curse, unsigned int, curse_cmd, curse_id_t, curse_no, pid_t, target)		//asmlinkage long sys_curse(int curse_cmd, int curse_no, pid_t target)
{	
	long ret = -EINVAL;
	int cmd_norm=(int)curse_cmd;

	printk(KERN_INFO "Master, you gave me command %d with curse %llu on pid %ld.\n", curse_cmd, curse_no, (long)target);
	
	//Do not even call if curse system is not active.
	#ifdef _CURSES_INSERTED
	switch(cmd_norm) {
	//	case LIST_ALL:			//Fall-through: read through proc.
	//		ret = syscurse_list_all();
	//		break;
		case ACTIVATE:
			ret = syscurse_activate(curse_no);
			break;
		case DEACTIVATE:
			ret = syscurse_deactivate(curse_no);
			break;
		case CHECK_CURSE_ACTIVITY:
			ret = syscurse_check_curse_activity(curse_no);
			break;
		case CHECK_TAINTED_PROCESS:
			ret = syscurse_check_tainted_process(curse_no, target);
			break;
		case CAST:
			ret = syscurse_cast(curse_no, target);
			break;
		case LIFT:
			ret = syscurse_lift(curse_no, target);
			break;
		case SHOW_RULES:
			//Stub (for now, fall-throughs).
		case ADD_RULE:
		case REM_RULE:
			printk(KERN_INFO "This operation is unsupported at this time.\n");
			goto out;
		case ILLEGAL_COMMAND:
		default:
			goto out;
	}
	#endif

out:
	return ret;
}

/*TODO: Source helpful functions.*/
int syscurse_list_all (char *page, char **start, off_t off, int count, int *eof, void *data) {
	int i, line_len, ret=0;
	struct syscurse *c_list=(struct syscurse *)data;

	printk(KERN_INFO "You called read with offset: %ld for count: %d , data: %p - %p and start: %p\n", (long)off, count, data, curse_list_pointer, start);
	if ((off>0) || (data==NULL)) {	//Dunno; see here:	http://www.thehackademy.net/madchat/coding/procfs.txt
		(*eof)=1;
		goto out;
	}

	//FIXME: Fix error: we have to predict that the next print will not cause overflow, so I am being overly cautious.
	line_len=sizeof(c_list[i].entry->curse_name)+sizeof(c_list[i].entry->curse_id);
	for (i=0; ((i<max_curse_no) && ((ret+line_len) < count)); i++)
		ret+=scnprintf(&page[ret], count, "%s %llX\n", c_list[i].entry->curse_name, c_list[i].entry->curse_id);
	(*start)=page;

out:
	return ret;
}

int syscurse_activate (curse_id_t curse_no) {
	int i, ret = -EPERM;

	//TODO: Check permissions.
	ret = -EINVAL;
	//TODO: Found a use for stub curse 0: activates the general curse system without activating any curse.
	if (bitmask_from_no(curse_no)) {											//Activation of an existing curse, activates the system too.
		i=index_from_no(curse_no);
		if (!(curse_list_pointer[i].status & (ACTIVATED|ACTIVE))) {
			curse_list_pointer[i].status = ACTIVATED;
			ret=1;
		} else {
			goto out_ret;
		}
	}
	if (!curse_system_active.value) {											//On invalid id, system activation.	::	TODO: Race here.
		if (down_interruptible(&curse_system_active.guard)) {
			ret = -EINTR;
			goto out_ret;
		}
		curse_system_active.value=1;
		up(&curse_system_active.guard);
	}

out_ret:
	return ret;
}

int syscurse_deactivate (curse_id_t curse_no) {
	int i, ret = -EPERM;

	//TODO: Check permissions.
	ret = -EINVAL;
	if (bitmask_from_no(curse_no)) {											//Targeted deactivation is normal.
		i=index_from_no(curse_no);
		if (curse_list_pointer[i].status & (ACTIVATED|ACTIVE)) {
			curse_list_pointer[i].status = IMPLEMENTED;
			ret=1;
		} else {
			goto out_ret;
		}
	} else if (/*!bitmask_from_no(curse_no) && */ curse_system_active.value) {	//Invalid target deactivates the system.
		if (down_interruptible(&curse_system_active.guard)) {
			ret = -EINTR;
			goto out_ret;
		}
		curse_system_active.value=0;
		up(&curse_system_active.guard);
	}
	//TODO: Do we have to unhook (call close pointer) all the active curses here?	::	No, we simply deactivate. On activation, it will continue as was.

out_ret:
	return ret;
}

int syscurse_check_curse_activity (curse_id_t curse_no) {
	int i, ret = -EINTR;

	if (down_interruptible(&curse_system_active.guard))
		goto out_pos;
	if (curse_system_active.value == 0)
		goto out_sema_held;
	i=index_from_no(curse_no);
	if (curse_list_pointer[i].entry->curse_id == 0xABADDE5C) {
		ret = -EINVAL;
		goto out_sema_held;
	}
    if (curse_list_pointer[i].status & ACTIVE)
        ret=1;
	else
		ret=0;

out_sema_held:
	up(&curse_system_active.guard);
out_pos:
	return ret;
}

int syscurse_check_tainted_process (curse_id_t curse_no, pid_t target) {
	int err = -EINVAL;
	uint64_t check_bit;
	unsigned long spinflags;
	struct task_struct *target_task;

	if (!(check_bit = bitmask_from_no(curse_no)) || (target <= 0))
		goto out;
	if ((err=down_interruptible(&curse_system_active.guard)))
		goto out;
	err = -ESRCH;

	rcu_read_lock();
	target_task = find_task_by_vpid(target);
	rcu_read_unlock();
	if (!target_task)
		goto out_locked;

	err = -EPERM;
	//TODO: Check permissions.
	//Check if target has an active curse on it.	::	TODO: Move it to one-liner? Is it better?
	spin_lock_irqsave(&((target_task->curse_data).protection) , spinflags);
	if (target_task->curse_data.curse_field & check_bit){
		err=1;
		printk(KERN_INFO "curse_field is %llu\n",target_task->curse_data.curse_field);
	} else {
		err=0;
		printk(KERN_INFO "no curse_field for you!\n");
	}
	spin_unlock_irqrestore(&((target_task->curse_data).protection), spinflags);

out_locked:
	up(&curse_system_active.guard);
out: 
	return err;
}

int syscurse_cast (curse_id_t curse_no, pid_t target) {
	int err;
	unsigned long spinflags;
	struct task_struct *target_task;
	int new_index;
	uint64_t new_mask;

	if ((err = down_interruptible(&curse_system_active.guard)))
		goto out;

	err = -ESRCH;
	rcu_read_lock();
	target_task = find_task_by_vpid(target);
	rcu_read_unlock();
	if (!target_task)
		goto out_locked;
	err = -EPERM;
	//TODO: Check permissions.

	err = -EINVAL;
	new_index = index_from_no(curse_no);
	if (!(new_mask = curse_list_pointer[new_index].curse_bit) && !(curse_list_pointer[new_index].status & (ACTIVATED|ACTIVE)))
		goto out_locked;
	spin_lock_irqsave(&((target_task->curse_data).protection), spinflags);
	if (!(target_task->curse_data.curse_field & new_mask)) {
		target_task->curse_data.curse_field |= new_mask;
		curse_list_pointer[new_index].ref_count++;
		if (GET_INHER(curse_list_pointer[new_index]))
			target_task->curse_data.inherritance |= new_mask;
		else
			target_task->curse_data.inherritance &= (~new_mask);
		curse_list_pointer[new_index].status=ACTIVE;
		err=1;
	}
	spin_unlock_irqrestore(&((target_task->curse_data).protection), spinflags);
	printk(KERN_INFO "Casting curse %llu to process %d\n",curse_no,target);

out_locked:
	up(&curse_system_active.guard);
out: 
	return err;
}

int syscurse_lift (curse_id_t curse_no, pid_t target) {
	int err = -EINVAL;
	unsigned long spinflags;
	struct task_struct *target_task;
	uint64_t curse_mask;
	int index;

	if ((err = down_interruptible(&curse_system_active.guard)))
		goto out;

	err = -ESRCH;
	rcu_read_lock();
	target_task = find_task_by_vpid(target);
	rcu_read_unlock();
	if (!target_task)
		goto out_locked;
	err = -EPERM;
	//TODO: Check permissions.

	err = -EINVAL;
	index = index_from_no(curse_no);
	if (!(curse_mask = curse_list_pointer[index].curse_bit))
		goto out_locked;
	spin_lock_irqsave(&((target_task->curse_data).protection), spinflags);
	if (target_task->curse_data.curse_field & curse_mask) {
		target_task->curse_data.curse_field &= (~curse_mask);		//Just to be safe (^= toggles, not clears).
		curse_list_pointer[index].ref_count--;
		target_task->curse_data.inherritance &= (~curse_mask);
		if (curse_list_pointer[index].ref_count == 0)			//Set curse status to ACTIVATED if ref 0ed-out.
			curse_list_pointer[index].status = ACTIVATED;
		err=1;
	}
	spin_unlock_irqrestore(&((target_task->curse_data).protection), spinflags);
	printk(KERN_INFO "Lifting curse %llu from process %d\n",curse_no,target);

out_locked:
	up(&curse_system_active.guard);
out:
	return err;
}

int syscurse_show_rules (void) {
	return 0;
}

int syscurse_add_rule (curse_id_t curse, char *path) {
	return 0;
}

int syscurse_rem_rule (curse_id_t curse, char *path) {
	return 0;
}
