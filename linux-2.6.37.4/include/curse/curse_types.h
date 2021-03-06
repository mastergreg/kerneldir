/*
 * This library is to be included in the sched/fs/exec/fork sources,
 * so as not to include unnecessary definitions and libraries.
 */

#ifndef _CURSE_TYPES_LIB
#define _CURSE_TYPES_LIB

typedef uint64_t curse_id_t;

/* Kernel-specific structures. */
#ifdef __KERNEL__

#include <linux/types.h>
#include <linux/spinlock.h>

#ifndef _CURSE_TASK_STRUCT_DEFINED
#define _CURSE_TASK_STRUCT_DEFINED

/*Curse specific data (linked list head element).*/
struct curse_inside_data {
	void *elem;
	curse_id_t owner;
	struct curse_inside_data *next;
};

/*Struct to-be injected in task_struct to let us keep tabs on processes.*/
struct task_curse_struct {
	spinlock_t protection;		//Because it is included in sched.h (and no semaphores are welcome there:))
	uint64_t triggered;
	uint64_t curse_field;
	uint64_t inherritance;		//Bitwise association of this field's bits and the previous one's.
	uint8_t permissions;

	uint32_t no_fs_cache_counter;
	uint32_t poison_counter;

	struct curse_specific_data {
		struct curse_inside_data *head;
	} use_by_interface;
};

#endif	/* _CURSE_TASK_STRUCT_DEFINED */

/*System call function pointer structure.*/
struct curse_fun_element {
	void (*fun_init) (struct task_struct * );
	void (*fun_destroy) (struct task_struct * );
	void (*fun_inject) (uint64_t);
};

#endif	/* __KERNEL__ */

/*Maximum size for a curse name.*/
#define CURSE_MAX_NAME_SIZE 24

/*Curse entry structure for logistic purposes.*/
struct __attribute__((packed)) curse_list_entry {
    char curse_name[CURSE_MAX_NAME_SIZE];
    curse_id_t curse_id;
};

#endif	/* _CURSE_TYPES_LIB */
