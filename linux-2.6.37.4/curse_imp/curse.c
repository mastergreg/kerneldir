/*
 * This file contains the source code for the curse system call.
 * 
 * [The functions used by the system call are sourced below it.]
 *
 */
 
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/types.h>		/*Sentinels prevent multiple inclusion.*/
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/proc_fs.h>
#include <linux/rcupdate.h>

#include <curse/curse.h>
#include <curse/curse_types.h>

//=====External declarations.
extern int max_curse_no;

//=====Various wrapper functions.
/*This function returns the index of the element with the specified curse id (or to the sentinel if invalid).*/
inline int index_normalizer (curse_id_t a_c_id) {
    int i = ((a_c_id < max_curse_no) ? a_c_id : max_curse_no);
	return i;
}

/*This function returns the bitmask for the specified curse id.*/
inline uint64_t bitmask_from_no (curse_id_t a_c_id) {
	return curse_list_pointer[index_normalizer(a_c_id)].curse_bit;
}

/*This macro expands to the requested field of the requested element of curse_list_pointer array.*/
#define CURSE_FIELD(el, field) (curse_list_pointer[(el)].field)

/*This function checks if current is allowed to change the state of the target proc.*/
inline int check_permissions (curse_id_t curse_no, pid_t target) {
	struct task_struct *foreign_task;
	const struct cred *foreign_c, *local_c;
	uint8_t local_curse_perms;
	uint8_t foreign_curse_perms;
	int ret;
	unsigned long spinflags;

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
	
	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	local_curse_perms = current->curse_data.permissions;
	spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);

	spin_lock_irqsave(&((foreign_task->curse_data).protection), spinflags);
	foreign_curse_perms = foreign_task->curse_data.permissions;
	spin_unlock_irqrestore(&((foreign_task->curse_data).protection), spinflags);

//	current_perms = CURSE_FIELD(index_normalizer(curse_no), permissions);
/*
	ret = -EPERM;
	if(((local_c->euid == 0) && (current_perms & _S_M))														|| \
		(((local_c->euid == foreign_c->euid) || (local_c->euid == foreign_c->uid)) && (current_perms & _U_M)))
		ret = 1;
*/
	printk(KERN_INFO "perm ret =%d\n", ret);
//out_with_local:
	put_cred(local_c);
out_with_foreign:
	put_cred(foreign_c);
out:
	return ret;
}

//=====Syscall kernel source.
/*This is the system call source base function.*/
SYSCALL_DEFINE4(curse, unsigned int, curse_cmd, curse_id_t, curse_no, pid_t, target, int, cur_ctrl)		//asmlinkage long sys_curse(int curse_cmd, int curse_no, pid_t target)
{	
	long ret = -EINVAL;
	int cmd_norm=(int)curse_cmd;

	printk(KERN_INFO "Master, you gave me command %d with curse %llu on pid %ld.\n", curse_cmd, curse_no, (long)target);
	
	//Do not even call if curse system is not active.
	#ifdef _CURSES_INSERTED
	switch(cmd_norm) {
		case LIST_ALL:
			ret = syscurse_list_all();
			break;
		case CURSE_CTRL:
			ret = syscurse_ctrl(curse_no, cur_ctrl, target);
			break;
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

//=====Source helpful sub-functions.
int syscurse_list_all (void) {
	int ret = -EINVAL;

	return ret;
}

int syscurse_activate (curse_id_t curse_no) {
	int i, ret = -EPERM;

	//TODO: Check permissions.
	if((ret = check_permissions(curse_no, 0) == -EPERM))
			goto out_ret;

	ret = -EINVAL;
	//TODO: Found a use for stub curse 0: activates the general curse system without activating any curse.
	if (bitmask_from_no(curse_no)) {								//Activation of an existing curse, activates the system too.
		i=index_normalizer(curse_no);
		if (!(CURSE_FIELD(i, status) & (ACTIVATED | CASTED))) {
			CURSE_FIELD(i, status) = ACTIVATED;
			ret=1;
		} else {
			goto out_ret;
		}
	}
	if (!CURSE_SYSTEM_Q)											//On invalid id, system activation.
		CURSE_SYSTEM_UP;

out_ret:
	return ret;
}

int syscurse_deactivate (curse_id_t curse_no) {
	int i, ret = -EPERM;

	//TODO: Check permissions.
	if((ret = check_permissions(curse_no, 0) == -EPERM))
			goto out_ret;

	ret = -EINVAL;
	if (bitmask_from_no(curse_no)) {								//Targeted deactivation is normal.
		i=index_normalizer(curse_no);
		if (CURSE_FIELD(i, status) & (ACTIVATED | CASTED)) {
			CURSE_FIELD(i, status) = IMPLEMENTED;
			ret=1;
		} else {
			goto out_ret;
		}
	} else if (/*!bitmask_from_no(curse_no) && */ CURSE_SYSTEM_Q)	//Invalid target deactivates the system.
		CURSE_SYSTEM_DOWN;

	//TODO: Do we have to unhook (call close pointer) all the active curses here?	::	No, we simply deactivate. On activation, it will continue as was.

out_ret:
	return ret;
}

int syscurse_check_curse_activity (curse_id_t curse_no) {
	int i, ret = -EINTR;

	if (!CURSE_SYSTEM_Q)
		goto out;

	i=index_normalizer(curse_no);
	if (CURSE_FIELD(i, entry)->curse_id == 0xABADDE5C) {
		ret = -EINVAL;
		goto out;
	}
	if (CURSE_FIELD(i, status) & CASTED)
		ret=1;
	else
		ret=0;

out:
	return ret;
}

int syscurse_check_tainted_process (curse_id_t curse_no, pid_t target) {
	int err = -EINVAL;
	uint64_t check_bit;
	unsigned long spinflags;
	struct task_struct *target_task;

	if (!(check_bit = bitmask_from_no(curse_no)) || (target <= 0))
		goto out;
	if (!CURSE_SYSTEM_Q)
		goto out;

	err = -ESRCH;
	rcu_read_lock();
	target_task = find_task_by_vpid(target);
	rcu_read_unlock();
	if (!target_task)
		goto out;

	//TODO: Check permissions.
	err = -EINVAL;
	if(target <= 0)
		goto out;
	if((err = check_permissions(curse_no, target) == -EPERM))
		goto out;
	err = 0;
	

	//Check if target has an active curse on it.	::	FIXME: Move it to one-liner? Is it better?
	spin_lock_irqsave(&((target_task->curse_data).protection), spinflags);
	if (target_task->curse_data.curse_field & check_bit){
		err=1;
		printk(KERN_INFO "curse_field is %llu\n",target_task->curse_data.curse_field);
	} else {
		err=0;
		printk(KERN_INFO "no curse_field for you!\n");
	}
	spin_unlock_irqrestore(&((target_task->curse_data).protection), spinflags);

out: 
	return err;
}

int syscurse_ctrl (curse_id_t curse_no, int ctrl, pid_t pid) {
	int index, ret = -EINVAL;
	struct task_struct *target_task;
	struct task_curse_struct *cur_curse_field;
	unsigned long flags=0;

	if ((index = index_normalizer(curse_no))) {
		goto out;
	} 

	spin_lock_irqsave(&CURSE_FIELD(index, perm_lock), flags);
	ret=1;
	switch (ctrl) {		/*Inherritance (on curse_list_ponter array)*/
		case INH_ON			:
			SET_INHER(index);
			break;
		case INH_OFF		:
			CLR_INHER(index);
			break;
		default:
			ret=-1;
	}
	spin_unlock_irqrestore(&CURSE_FIELD(index, perm_lock), flags);

	if (ret == 1)
		goto out;

	rcu_read_lock();
	target_task = find_task_by_vpid(pid);
	rcu_read_unlock();
	if (!target_task)
		goto out;
	cur_curse_field = &(target_task->curse_data);
	
	//TODO: Check permissions.

	spin_lock_irqsave(&(cur_curse_field->protection), flags);
	switch (ctrl) {		/*Permissions (on task_curse_struct struct)*/
		case USR_PERM_ON	:
			SET_PERM((*cur_curse_field), (_USR_ACTIVE_PERM|_USR_PASSIVE_PERM));
			break;
		case GRP_PERM_ON	:
			SET_PERM((*cur_curse_field), (_GRP_ACTIVE_PERM|_GRP_PASSIVE_PERM));
			break;
		case SU_PERM_ON		:
			SET_PERM((*cur_curse_field), (_SU_ACTIVE_PERM|_SU_PASSIVE_PERM));
			break;
		case USR_PERM_OFF	:
			CLR_PERM((*cur_curse_field), (_USR_ACTIVE_PERM|_USR_PASSIVE_PERM));
			break;
		case GRP_PERM_OFF	:
			CLR_PERM((*cur_curse_field), (_GRP_ACTIVE_PERM|_GRP_PASSIVE_PERM));
			break;
		case SU_PERM_OFF	:
			CLR_PERM((*cur_curse_field), (_SU_ACTIVE_PERM|_SU_PASSIVE_PERM));
			break;
		default				:
			ret = -EINVAL;
	}
	spin_unlock_irqrestore(&(cur_curse_field->protection), flags);

out:
	return ret;
}

int syscurse_cast (curse_id_t curse_no, pid_t target) {
	int err = -EINVAL;
	unsigned long spinflags;
	struct task_struct *target_task;
	int new_index;
	uint64_t new_mask;

	if (!CURSE_SYSTEM_Q)
		goto out;

	err = -ESRCH;
	rcu_read_lock();
	target_task = find_task_by_vpid(target);
	rcu_read_unlock();
	if (!target_task)
		goto out;

	//TODO: Check permissions.
	err = -EINVAL;
	if(target <= 0 )
		goto out;
	if((err = check_permissions(curse_no, target) == -EPERM))
		goto out;
	err = 0;

	err = -EINVAL;
	new_index = index_normalizer(curse_no);
	if (!(new_mask = CURSE_FIELD(new_index, curse_bit)) && !(CURSE_FIELD(new_index, status) & (ACTIVATED | CASTED)))
		goto out;
	spin_lock_irqsave(&((target_task->curse_data).protection), spinflags);
	if (!(target_task->curse_data.curse_field & new_mask)) {
		target_task->curse_data.curse_field |= new_mask;
		atomic_inc(&CURSE_FIELD(new_index, ref_count));
		if (GET_INHER(new_index))
			target_task->curse_data.inherritance |= new_mask;
		else
			target_task->curse_data.inherritance &= (~new_mask);
		CURSE_FIELD(new_index, status) = CASTED;
		err=1;
	}
	spin_unlock_irqrestore(&((target_task->curse_data).protection), spinflags);

	CURSE_FIELD(new_index, functions)->fun_init();

	printk(KERN_INFO "Casting curse %llu to process %d %llx\n",curse_no,target,new_mask);

out: 
	return err;
}

int syscurse_lift (curse_id_t curse_no, pid_t target) {
	int err = -EINVAL;
	unsigned long spinflags;
	struct task_struct *target_task;
	uint64_t curse_mask;
	int index;

	if (!CURSE_SYSTEM_Q)
		goto out;

	err = -ESRCH;
	rcu_read_lock();
	target_task = find_task_by_vpid(target);
	rcu_read_unlock();
	if (!target_task)
		goto out;
	
	//TODO: Check permissions.
	err = -EINVAL;
	if(target <= 0)
		goto out;
	if((err = check_permissions(curse_no, target) == -EPERM))
		goto out;

	err = -EINVAL;
	index = index_normalizer(curse_no);
	if (!(curse_mask = CURSE_FIELD(index, curse_bit)))
		goto out;
	spin_lock_irqsave(&((target_task->curse_data).protection), spinflags);
	if (target_task->curse_data.curse_field & curse_mask) {
		target_task->curse_data.curse_field &= (~curse_mask);		//Just to be safe (^= toggles, not clears).
		atomic_dec(&CURSE_FIELD(index, ref_count));
		target_task->curse_data.inherritance &= (~curse_mask);
		if (atomic_read(&CURSE_FIELD(index, ref_count)) == 0)		//Revert curse status to ACTIVATED if ref 0ed-out.	: Could be atomic_dec_and_set.
			CURSE_FIELD(index, status) = ACTIVATED;
		err=1;
	}
	spin_unlock_irqrestore(&((target_task->curse_data).protection), spinflags);
	printk(KERN_INFO "Lifting curse %llu from process %d\n",curse_no,target);

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
