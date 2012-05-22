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
#include <asm/atomic.h>

#include "curse.h"
#include "curse_list.h"
//Global data (create them taking into account reentrancy: static usually prevents that).
/*This flag helps to initialize what needs initializing in our envirronment.*/
atomic_t initial_actions_flag = { 1 };		//Check for info: http://www.win.tue.nl/~aeb/linux/lk/lk-13.html

//Other functions.
/*This function initializes all needed resources (only) once, at the beginning.*/
void initial_actions (void) {
	//Global activity status.
	printk(KERN_INFO "Entered initialization function.\n");		//Testing if it is really called only the first time.
	sema_init(&curse_system_active.guard, 1);
	curse_system_active.value=0;
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
	
	switch(cmd_norm) {
		case LIST_ALL:
            ret = syscurse_list_all();
            break;
		case ACTIVATE:
            ret = syscurse_activate();
            break;
		case DEACTIVATE:
            ret = syscurse_deactivate();
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

out:
	return ret;
	//return (long)(curse_cmd+curse_no+(int)target);
}

//TODO: Some functions should not return int, but a pointer to an array (for example syscurse_list_all, I think).
//IMPORTANT: Depending on the way we do the copy to userspace, this should not even matter. I think it would be better if we went with the proc filesystem mapping solution (it is not a case where the data is time sensitive).

//TODO: Source helpful functions.
int syscurse_list_all (void) {
	//...
	return 0;
}
int syscurse_activate (void) {
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
int syscurse_deactivate (void) {
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
out_sema_held:
	up(&curse_system_active.guard);
out_pos:
	return ret;
}
int syscurse_check_tainted_process (pid_t target) {
	int err=-EINVAL;
	struct task_struct *target_task;
	#ifdef _CURSES_INSERTED
		if ((err=down_interruptible(&curse_system_active.guard)))
			goto out;
		err = -EINVAL;
		if (target<=0)
			goto out_locked;
		err = -ESRCH;
		target_task = find_task_by_vpid(target);
		if (!target_task)
			goto out_locked;
		//STUB: Check if target has an active curse on it.	::	TODO: Move it to one-liner? Is t better?
			if (target_task->curse_data.curse_field)
				err=0;
			else
				err=1;
		//...
out_locked:
		up(&curse_system_active.guard);
	#endif
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

