/*
 * This file is part of the interface between the curses mechanism
 * and the curses implementation.
 * Every curse available must be registered here.
 * TODO: Maybe we could add a description field in each curse.
 * 
 */

#ifndef _CURSE_LIST_LIB
#define _CURSE_LIST_LIB

#include <linux/types.h>

/*Maximum size for a curse name.*/
#define CURSE_MAX_NAME_SIZE 24
/*Maximum number of curses (-1 is the limit).*/
#define MAX_CURSE_NO 65

/*Curse entry structure for logistic purposes.*/
struct curse_list_entry {
	char curse_name[CURSE_MAX_NAME_SIZE];
	uint64_t curse_id;
};

#ifdef __KERNEL__

/*[ADD] The individual curse header includes.*/
static inline void stub_init(void /*or not*/) {
    return;
}
static inline void stub_destroy(void /*or not*/) {
    return;
}
static inline void stub_use(void /*not*/) {
    return;
}

/*[ADD] The system curse listing.*/
struct curse_list_entry curse_full_list[] = {
	{	"stub", 0x00000000	},
	
	{	"opalakia", 0x00000001	},
	{	"another_entry", 0x00000080	},
	
	{	"sentinel", 0xABADDE5C	}	/*Curse table sentinel. Every entry after this will be ignored.*/
};

/*System call function pointer structure.*/
struct fun_element {
	void (*fun_init)(void /*List of arguments*/);
	void (*fun_destroy)(void /*List of arguments*/);
	void (*fun_use)(void /*List of arguments*/);
};

/*[ADD] The system call function pointer array.*/
struct fun_element fun_array[] = {
	{	stub_init, stub_destroy, stub_use	}, /* maybe a stub maybe not, depends on how we handle 0 */

	{	stub_init, stub_destroy, stub_use	},
	{	stub_init, stub_destroy, stub_use	},

	{	stub_init, stub_destroy, stub_use	} /* you have made a grave mistace (sentinel speaking) */
};

#endif	/* __KERNEL__ */

#endif /* _CURSE_LIST_LIB */

