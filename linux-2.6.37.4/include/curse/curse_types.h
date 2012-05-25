/*
 * This library is to be included in the sched/fs/exec/fork sources, 
 * so as not to include unnecessary definitions and libraries.
 */

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
	uint64_t curse_field;
	uint64_t inherritance;		//Bitwise association of this field's bits and the previous one's.
};

#ifndef _CURSE_TYPES_LIB
#define _CURSE_TYPES_LIB
#endif

typedef uint64_t curse_id_t;

#endif	/* _CURSE_TASK_STRUCT_DEFINED */
