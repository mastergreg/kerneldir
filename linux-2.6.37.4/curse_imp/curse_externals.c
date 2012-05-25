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

#include <curse/curse_list.h>
#include <curse/curse_types.h>
/*
#include <curse/curse.h>
#include <curse/curse_forwards.h>
*/
/*This is the injection wrapper, which must be in kernel space. This basically is an inline or define directive that checks if curses are activated and if the current process has a curse before calling the proper curse function.*/
inline void curse_k_wrapper (void) {
	//check if curses are enabled
	struct task_struct *cur;

	if (down_interruptible(&curse_system_active.guard))
		goto out_pos;
	//check if current has a curse
	if (curse_system_active.value == 0)
		goto out_sema_held;
	//this is a macro in arch/x86/include/asm/current.h
	cur = current;

	//call the curse handler if there is a curse
	//if is used for opt, might integrate the handler here
	//ideas?
	if (cur->curse_data.curse_field) {
		int i=1;
		uint64_t c_m=0x0001, c_f = cur->curse_data.curse_field;
		printk(KERN_INFO "Gotta do sth now, whaaat?\n");
		
		//... This is where curse and check take place.
		while ((c_f & c_m) || (c_f)) {		//While the current is active, or there are remaining fields:
			fun_array[i].fun_inject();
			c_f >>= 1;
			i++;
		}
	}

out_sema_held:
	up(&curse_system_active.guard);
out_pos:
	return;
}

/*This function initializes all needed resources (only) once, at the beginning.*/
void curses_init (void) {
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

