/*
 * This library is to be included in the sched/fs/exec/fork sources,
 * so as not to include unnecessary definitions and libraries.
 */

#ifndef _CURSE_TYPES_LIB
#define _CURSE_TYPES_LIB

/* Kernel-specific structures. */
#ifdef __KERNEL__

#include <linux/spinlock.h>

#ifndef _CURSE_TASK_STRUCT_DEFINED
#define _CURSE_TASK_STRUCT_DEFINED

/*Preprocessor guard for scheduling/execing.*/
#ifndef _CURSES_INSERTED
#define _CURSES_INSERTED
#endif

/*Struct to-be injected in task_struct to let us keep tabs on processes.*/
struct task_curse_struct {
	spinlock_t protection;		//Because it is included in sched.h (and no semaphores are welcome there:))
	uint64_t triggered;
	uint64_t curse_field;
	uint64_t inherritance;		//Bitwise association of this field's bits and the previous one's.
	uint8_t permissions;
	uint32_t no_fs_cache_counter;
};

#endif	/* _CURSE_TASK_STRUCT_DEFINED */

/*System call function pointer structure.*/
struct curse_fun_element {
	void (*fun_init) (void /*List of arguments*/);
	void (*fun_destroy) (void /*List of arguments*/);
	void (*fun_inject) (uint64_t /*List of arguments*/);
};

#endif	/* __KERNEL__ */

typedef uint64_t curse_id_t;

/*Maximum size for a curse name.*/
#define CURSE_MAX_NAME_SIZE 24

/*Curse entry structure for logistic purposes.*/
struct curse_list_entry {
	char curse_name[CURSE_MAX_NAME_SIZE];
	curse_id_t curse_id;
};

#endif	/* _CURSE_TYPES_LIB */
