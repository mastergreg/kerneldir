#include <linux/compiler.h>
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
//#include <asm/current.h>		//Does it compile without this?
#include <asm/atomic.h>

#include <curse/curse_list.h>
#include <curse/curse_types.h>
#include <curse/curse.h>		//Now it is only needed for the macros.

//=====Global data.
/*Pointer to the implemented curse array (loaded at init of syscall).*/
struct syscurse *curse_list_pointer=(struct syscurse *)NULL;
/*Proc node pointer.*/
struct proc_dir_entry *dir_node=(struct proc_dir_entry *)NULL, *output_node=(struct proc_dir_entry *)NULL;

//=====Helpful functions (locally needed).		//TODO: We shouldn't add symbols we don't need to be external.
//FIXME: Couldn't we add a macro in curse_externals.h that changes id to mask during compilation. ::Possible conflicts with curse_init, that creates the masks.
inline int index_from_curse_id (curse_id_t _) {
	int i=0;

	if (_ == 0x00)
		goto out;
	for (i=1; i<MAX_CURSE_NO; i++)
		if ((curse_list_pointer[i].entry->curse_id) == _)
			goto out;

out:
	return i;
}

//=====Kernel functions.
#ifdef _CURSES_INSERTED

/*This is the injection wrapper, which must be in kernel space. This basically is an inline or define directive that checks if curses are activated and if the current process has a curse before calling the proper curse function.*/
void curse_k_wrapper (void) {
	struct task_struct *cur;

	if (!CURSE_SYSTEM_Q)
		goto out;

	cur = current;
	//call the curse handler if there is a curse
	//if is used for opt, might integrate the handler here
	//ideas?
//	printk("Curse on scheduler.\n");
	if (cur->curse_data.curse_field) {
		int i=1;
		uint64_t c_m=0x0001, c_f = (cur->curse_data.curse_field & cur->curse_data.triggered);
		printk(KERN_INFO "Gotta do sth now, whaaat?\n");
		
		//... This is where check and curse take place.
		while ((c_f & c_m) || (c_f)) {		//While the current is active, or there are remaining fields:
			fun_array[i].fun_inject(curse_list_pointer[i].curse_bit);
			c_f >>= 1;
			i++;
		}
		cur->curse_data.triggered = 0x0;
	}

out:
	return;
} 

int proc_curse_read (char *page, char **start, off_t off, int count, int *eof, void *data) {
	int i, line_len, ret=0;
	/*We provided the data pointer during creation of read handler for our proc entry.*/
	struct syscurse *c_list=(struct syscurse *)data;

	printk(KERN_INFO "You called read with offset: %ld for count: %d , data: %p - %p and start: %p\n", (long)off, count, data, curse_list_pointer, start);
	if ((off>0) || (data==NULL)) {	//Dunno; see here:	http://www.thehackademy.net/madchat/coding/procfs.txt	: We do not support reading continuation.
		(*eof)=1;
		goto out;
	}

	//FIXME: Fix exaggeration: we have to predict that the next print will not cause an overflow, so I am being overly cautious.
	line_len=sizeof(c_list[i].entry->curse_name)+sizeof(c_list[i].entry->curse_id);
	for (i=0; ((i<max_curse_no) && ((ret+line_len) < count)); i++)
		ret+=scnprintf(&page[ret], count, "%s %llX\n", c_list[i].entry->curse_name, c_list[i].entry->curse_id);
	(*start)=page;

out:
	return ret;
}

/*This function initializes all needed resources (only) once, during system init.*/
void curse_init (void) {
	int j;
	curse_id_t t;

	//1. Initialize curse lookup table.
	curse_list_pointer=(struct syscurse *)kzalloc((MAX_CURSE_NO+1)*sizeof(struct syscurse), GFP_KERNEL);
	for (j=1, t=0x01; j<MAX_CURSE_NO; j++, t<<=1) {
		curse_list_pointer[j].entry=(struct curse_list_entry *)&curse_full_list[j];
		curse_list_pointer[j].curse_bit=t;
		atomic_set(&(curse_list_pointer[j].ref_count), 0);
		curse_list_pointer[j].var_flags=_INHER_MASK;
		SET_INHER(j);
		curse_list_pointer[j].status=IMPLEMENTED;
		spin_lock_init(&(curse_list_pointer[j].flag_lock));
		curse_list_pointer[j].functions=&fun_array[j];
	}
	curse_list_pointer[0].status=INVALID_CURSE;
	curse_list_pointer[0].curse_bit=0x0;
	atomic_set(&(curse_list_pointer[0].ref_count), 0);
	curse_list_pointer[0].entry=(struct curse_list_entry *)&curse_full_list[0];
	spin_lock_init(&(curse_list_pointer[0].flag_lock));
	curse_list_pointer[0].functions=&fun_array[0];

	//2. Initialize active status boolean.	::	Could default on an initial status here (based on build options).
	CURSE_SYSTEM_DOWN;

	//3. Populate entries in /proc filesystem.
	if (!(dir_node = proc_mkdir(PROC_DIR_NAME, NULL)))
		goto out;
	if (!(output_node = create_proc_read_entry(PROC_OUT_NODE_NAME, (S_IRUSR|S_IRGRP|S_IROTH), dir_node, proc_curse_read, curse_list_pointer)))
		goto out_dirred;

	//FIXME: Is there anything else to be done here?

	goto out;
//out_nodded:
	remove_proc_entry(PROC_OUT_NODE_NAME, dir_node);
out_dirred:
	remove_proc_entry(PROC_DIR_NAME, NULL);
out:
	return;		//Stub: there might be others below.
}

/*This function is inserted in the places of the kernel source code that act as triggers for each curse, and inserts a trigger indicator in task struct of each task.*/
//FIXME: Have to swap out with define directive. Also, remove excessive overhead.
void curse_trigger (_Bool defer_action, curse_id_t cid) {
	struct task_curse_struct *cur_struct;
	unsigned long spinf;
	int index;

//	printk("Trigger on %lld\n", cid);
	index = index_from_curse_id(cid);

	cur_struct = &(current->curse_data);

	if (!unlikely(defer_action)) {
		(curse_list_pointer[index].functions)->fun_inject(curse_list_pointer[index].curse_bit);
	} else {
		spin_lock_irqsave(&(cur_struct->protection), spinf);
		cur_struct->triggered &= (curse_list_pointer[index].curse_bit);
		spin_unlock_irqrestore(&(cur_struct->protection), spinf);
	}

 }

#else	/*Define dummies here, for the case when the curses system is not inserted in the kernel code.*/

void curse_k_wrapper (void) {
	return;
}

void curse_init (void) {
	return;
}

void curse_trigger (curse_id_t _) {
	return;
} 

#endif	/* _CURSES_INSERTED */

