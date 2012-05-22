/*
 * This file contains the source code for the curse system call.
 * 
 * [The functions used by the system call are declared prior to the call source and sourced below it.]
 *
 */
 
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/types.h>		//Sentinels prevent multiple inclusion.
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <asm/atomic.h>
#include <linux/slab.h>

#include <curse/curse.h>
#include <curse/curse_list.h>

//Global data (create them taking into account reentrancy: static usually prevents that).
/*This flag helps to initialize what needs initializing in our envirronment.*/
atomic_t initial_actions_flag = { 1 };		//Check for info: http://www.win.tue.nl/~aeb/linux/lk/lk-13.html

//Other functions.
/*This function initializes all needed resources (only) once, at the beginning.*/
void initial_actions (void) {
	int i, j;
	//Global activity status.
	printk(KERN_INFO "Entered initialization function.\n");		//Testing if it is really called only the first time.
	//1. Initialize active status boolean.
	sema_init(&curse_system_active.guard, 1);
	curse_system_active.value=0;
	//2. Initialize curse lookup table.
	for (i=0; (curse_full_list[i].curse_id!=0xBADDE5C && i<MAX_CURSE_NO); i++) ;
	curse_list_pointer=(struct syscurse *)kzalloc((i+1)*sizeof(struct syscurse), GFP_KERNEL);
	for (j=0; j<i; j++) {
		curse_list_pointer[j].entry=(struct curse_list_entry *)&curse_full_list[j];
		curse_list_pointer[j].status=IMPLEMENTED;
	}
	printk(KERN_INFO "all ok. malloced");
	for (j=0; j<i; j++) {
		printk(KERN_INFO "name: %s -> id: %zu", curse_list_pointer[j].entry->curse_name, curse_list_pointer[j].entry->curse_id);
		printk(KERN_INFO "status: %d", curse_list_pointer[j].status);
	}
	printk(KERN_INFO "all printed");
}

/*This is the system call source base function.*/
SYSCALL_DEFINE3(curse, int, curse_cmd, int, curse_no, pid_t, target)		//asmlinkage long sys_curse(int curse_cmd, int curse_no, pid_t target)
{	
	long ret=-EINVAL;
	int cmd_norm=(int)curse_cmd;

	if (atomic_read(&initial_actions_flag)) {		//Conditional will not be entered but the first time(s).
		if (atomic_read(&initial_actions_flag)==2)
			goto wait_init;
		atomic_set(&initial_actions_flag, 2);
		//Initializing actions.
		initial_actions();
		atomic_set(&initial_actions_flag, 0);
		wait_init:
		while (atomic_read(&initial_actions_flag))
			continue;
	}

	printk(KERN_INFO "Master, you gave me command %d with curse %d on pid %ld.\n", curse_cmd, curse_no, (long)target);
	
	//Do not even call if curse system is not active.
	#ifdef _CURSES_INSERTED
	switch(cmd_norm) {
		case LIST_ALL:
            ret = syscurse_list_all();
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
            ret = syscurse_check_tainted_process(target);
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
			printk(KERN_INFO "This operation is unsupported at this time.");
            ret = -EINVAL;
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

//TODO: Source helpful functions.
int syscurse_list_all (void) {
	//...
	return 0;
}
int syscurse_activate (int curse_no) {
	//TODO: Found a use for stub curse 0: activates the general curse system without activating any curse.
	//TODO: On the other hand, activation of  a particular curse, implies activation of system.
	//FIXME...
	if (!curse_system_active.value) {
		if (down_interruptible(&curse_system_active.guard))
			return -EINTR;
		curse_system_active.value=1;
		up(&curse_system_active.guard);
	} else {
		return -EINVAL;
	}
	return 0;
}
int syscurse_deactivate (int curse_no) {
	if (curse_system_active.value) {
		if (down_interruptible(&curse_system_active.guard))
			return -EINTR;
		curse_system_active.value=0;
		up(&curse_system_active.guard);
	} else {
		return -EINVAL;
	}
	//TODO: Do we have to unhook (call close pointer) all the active curses here?
	return 0;
}
int syscurse_check_curse_activity (int curse_no) {
	int ret=-EINVAL;
	if (down_interruptible(&curse_system_active.guard))
		goto out_pos;
	if (curse_system_active.value==0)
		goto out_sema_held;
	//STUB: Check if any curse in the table is active.
	//...
    //8a exoume max
    if (curse_list_pointer[curse_no].status & ACTIVE) 
        ret = 0;
out_sema_held:
	up(&curse_system_active.guard);
out_pos:
	return ret;
}
int syscurse_check_tainted_process (pid_t target) {
	int err; 
	unsigned long spinflags;
	struct task_struct *target_task;

	if ((err=down_interruptible(&curse_system_active.guard)))
		goto out;
	err = -EINVAL;
	if (target<=0)
		goto out_locked;
	err = -EPERM;
	//STUB: Check permissions on current.
	err = -ESRCH;
	target_task = find_task_by_vpid(target);
	if (!target_task)
		goto out_locked;
	//Check if target has an active curse on it.	::	TODO: Move it to one-liner? Is it better?
	spin_lock_irqsave(&((target_task->curse_data).protection) , spinflags);
	if (target_task->curse_data.curse_field){
		err = 0;
		printk(KERN_INFO "curse_field is %llu",target_task->curse_data.curse_field);
	} else {
		err=1;
		printk(KERN_INFO "no curse_field for you!");
	}
	spin_unlock_irqrestore(&((target_task->curse_data).protection), spinflags);

out_locked:
	up(&curse_system_active.guard);
out: 
	return err;
}
int syscurse_cast (int curse_no, pid_t target) {
	//...
	return 0;
}
int syscurse_lift (int curse_no, pid_t target) {
	//...
	return 0;
}
int syscurse_show_rules (void) {
	return 0;
}
int syscurse_add_rule (int curse, char *path) {
	return 0;
}
int syscurse_rem_rule (int curse, char *path) {
	return 0;
}

