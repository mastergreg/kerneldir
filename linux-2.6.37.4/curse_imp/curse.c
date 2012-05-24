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

#include <curse/curse.h>
#include <curse/curse_list.h>

//Global data (create them taking into account reentrancy: static usually prevents that).
/*This flag helps to initialize what needs initializing in our envirronment.*/
atomic_t initial_actions_flag = { 1 };		//Check for info: http://www.win.tue.nl/~aeb/linux/lk/lk-13.html

//Other functions.
/*This function returns the index of the element with the specified curse id (or to the sentinel if invalid).*/
inline int index_from_id (uint64_t a_c_id) {
	return (int)((a_c_id<MAX_CURSE_NO) ? i : MAX_CURSE_NO);
}

/*This function returns the bitmask for the specified curse id.*/
inline uint64_t bitmask_from_id (uint64_t a_c_id) {
	return curse_list_pointer[index_from_id(a_c_id)].curse_bit;
}

/*This function checks if current is allowed to change the state of the target proc.*/
inline int check_permissions (pid_t target) {
	struct task_struct *foreign_task;
	const struct cred *foreign_c, *local_c;
	int ret;

	ret = -ESRCH;		//FIXME: Sanity check.
	foreign_task = find_task_by_vpid(target);
	if (!foreign_task)
		goto out;
	ret = -EINVAL;		//FIXME: Sanity check.
	foreign_c = get_task_cred(foreign_task);
	if (!foreign_c)
		goto out_with_foreign;

	local_c = get_current_cred();
	ret = ((local_c->uid == 0) || (local_c->uid == foreign_c->uid) || (local_c->gid == foreign_c->gid));
	//Maybe we should use (if even one of the conditions is true, we have permission to interfere) :
	// ! ((a->euid != 0) || (a->euid != b->uid) || (a->euid != b->euid) || (a->gid != b->gid) || !capable(ACTION))
	// ... where ACTION is a function parameter.

//out_with_local:
	put_cred(local_c);
out_with_foreign:
	put_cred(foreign_c);
out:
	return ret;
}

/*This function initializes all needed resources (only) once, at the beginning.*/
void initial_actions (void) {
	int j;
	curse_id_t t;

	//Global activity status.
	printk(KERN_INFO "Entered initialization function.\n");		//Testing if it is really called only the first time.

	//1. Initialize active status boolean.
	sema_init(&curse_system_active.guard, 1);
	curse_system_active.value = 0;

	//2. Initialize curse lookup table.
	curse_list_pointer=(struct syscurse *)kzalloc((MAX_CURSE_NO+1)*sizeof(struct syscurse), GFP_KERNEL);
	for (j=0, t=0x01; j<MAX_CURSE_NO; j++, t<<=1) {
		curse_list_pointer[j].entry=(struct curse_list_entry *)&curse_full_list[j];
		curse_list_pointer[j].curse_bit=t;
		curse_list_pointer[j].ref_count=0;
		curse_list_pointer[j].permissions=(_S_M | _G_M | _U_M);
		SET_INHER(curse_list_pointer[j]);
		curse_list_pointer[j].status=IMPLEMENTED;
	}
	curse_list_pointer[0].status=INVALID_CURSE;
	curse_list_pointer[0].curse_bit=0x0;
	curse_list_pointer[0].ref_count=0;
	curse_list_pointer[0].entry=(struct curse_list_entry *)&curse_full_list[0];

	//3. Populate entries in /proc filesystem.
	if (!(dir_node = proc_mkdir(proc_dir_name, NULL)))
		goto out;
	if (!(output_node = create_proc_read_entry(proc_out_node_name, (S_IRUSR|S_IRGRP|S_IROTH), dir_node, syscurse_list_all, curse_list_pointer)))
		goto out_dirred;
	//FIXME: Is there anything else to be done here?

	goto out;
//out_nodded:
	remove_proc_entry(proc_out_node_name, dir_node);
out_dirred:
	remove_proc_entry(proc_dir_name, NULL);
out:
	return;		//Stub, but there might be others below.
}

/*This is the system call source base function.*/
SYSCALL_DEFINE3(curse, unsigned int, curse_cmd, uint64_t, curse_no, pid_t, target)		//asmlinkage long sys_curse(int curse_cmd, int curse_no, pid_t target)
{	
	long ret = -EINVAL;
	int cmd_norm=(int)curse_cmd;

	if (atomic_read(&initial_actions_flag)) {		//Conditional will not be entered but the first time(s).	//FIXME: I think it disables local interests. We can protect it with a single boolean.
		if (atomic_read(&initial_actions_flag) == 2)
			goto wait_init;
		atomic_set(&initial_actions_flag, 2);
		//Initializing actions.
		initial_actions();
		atomic_set(&initial_actions_flag, 0);
		wait_init:
		while (atomic_read(&initial_actions_flag))
			continue;
	}

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
	//return (long)(curse_cmd+curse_no+(int)target);
}

/*TODO: Source helpful functions.*/
int syscurse_list_all (char *page, char **start, off_t off, int count, int *eof, void *data) {
	int i, line_len, ret=0;
	struct syscurse *c_list=(struct syscurse *)data;

//	printk(KERN_INFO "You called read with offset: %ld for count: %d , data: %p - %p and start: %p\n", (long)off, count, data, curse_list_pointer, start);
	if ((off>0) || (data==NULL)) {	//Dunno; see here:	http://www.thehackademy.net/madchat/coding/procfs.txt
		(*eof)=1;
		goto out;
	}
	//FIXME: Fix error: we have to predict that the next print will not cause overflow, so I am being overly cautious.
	line_len=sizeof(c_list[i].entry->curse_name)+sizeof(c_list[i].entry->curse_id);
	for (i=0; ((c_list[i].entry->curse_id != 0xABADDE5C) && ((ret+line_len) < count)); i++)
		ret+=scnprintf(&page[ret], count, "%s %llX\n", c_list[i].entry->curse_name, c_list[i].entry->curse_id);

out:
	return ret;
}

int syscurse_activate (uint64_t curse_no) {
	int i, ret = -EPERM;

	//TODO: Check permissions.
	ret = -EINVAL;
	//TODO: Found a use for stub curse 0: activates the general curse system without activating any curse.
	if (bitmask_from_id(curse_no)) {											//Activation of an existing curse, activates the system too.
		for (i=0; (curse_list_pointer[i].entry->curse_id != curse_no); i++)
			;
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

int syscurse_deactivate (uint64_t curse_no) {
	int i, ret = -EPERM;

	//TODO: Check permissions.
	ret = -EINVAL;
	if (bitmask_from_id(curse_no)) {											//Targeted deactivation is normal.
		for (i=0; (curse_list_pointer[i].entry->curse_id != curse_no); i++)
			;
		if (curse_list_pointer[i].status & (ACTIVATED|ACTIVE)) {
			curse_list_pointer[i].status = IMPLEMENTED;
			ret=1;
		} else {
			goto out_ret;
		}
	} else if (/*!bitmask_from_id(curse_no) && */ curse_system_active.value) {	//Invalid target deactivates the system.
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

int syscurse_check_curse_activity (uint64_t curse_no) {
	int i, ret = -EINTR;

	if (down_interruptible(&curse_system_active.guard))
		goto out_pos;
	if (curse_system_active.value == 0)
		goto out_sema_held;
	for (i=0; ((curse_list_pointer[i].entry->curse_id != curse_no) && (curse_list_pointer[i].entry->curse_id != 0xABADDE5C)); i++)
		;
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

int syscurse_check_tainted_process (uint64_t curse_no, pid_t target) {
	int err = -EINVAL;
	uint64_t check_bit;
	unsigned long spinflags;
	struct task_struct *target_task;

	if (!(check_bit = bitmask_from_id(curse_no)) || (target <= 0))
		goto out;
	if ((err=down_interruptible(&curse_system_active.guard)))
		goto out;
	err = -ESRCH;
	target_task = find_task_by_vpid(target);
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

int syscurse_cast (uint64_t curse_no, pid_t target) {
	int err;
	unsigned long spinflags;
	struct task_struct *target_task;
	int new_index;
	uint64_t new_mask;

	if ((err = down_interruptible(&curse_system_active.guard)))
		goto out;

	err = -ESRCH;
	target_task = find_task_by_vpid(target);
	if (!target_task)
		goto out_locked;
	err = -EPERM;
	//TODO: Check permissions.

	err = -EINVAL;
	new_index = index_from_id(curse_no);
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

int syscurse_lift (uint64_t curse_no, pid_t target) {
	int err = -EINVAL;
	unsigned long spinflags;
	struct task_struct *target_task;
	uint64_t curse_mask;
	int index;

	if ((err = down_interruptible(&curse_system_active.guard)))
		goto out;

	err = -ESRCH;
	target_task = find_task_by_vpid(target);
	if (!target_task)
		goto out_locked;
	err = -EPERM;
	//TODO: Check permissions.

	err = -EINVAL;
	index = index_from_id(curse_no);
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

int syscurse_add_rule (uint64_t curse, char *path) {
	return 0;
}

int syscurse_rem_rule (uint64_t curse, char *path) {
	return 0;
}
