/*
 * This file is part of the interface between the curses mechanism
 * and the curses implementation.
 * Every curse available must be registered here.
 * TODO: Maybe we could add a description field in each curse.
 * 
 */

#include <linux/types.h>

/*Maximum size for a curse name.*/
#define CURSE_MAX_NAME_SIZE 24

/*Curse entry structure for logistic purposes.*/
struct curse_list_entry {
	char curse_name[CURSE_MAX_NAME_SIZE];
	uint64_t curse_id;
};


/*
 * this could be used instead of all the defines
 * style is everything :p FIXME

enum commands{  LIST_ALL=0,
		        ACTIVATE,
		        DEACTIVATE,
		        CHECK_CURSE_ACTIVITY,
		        CHECK_TAINTED_PROCESS,
		        DEPLOY,
		        RETIRE,
		        SHOW_RULES,
		        ADD_RULE,
		        REM_RULE,
                NR_COMMANDS
}

 */

#define LIST_ALL                0
#define ACTIVATE                1
#define DEACTIVATE              2
#define CHECK_CURSE_ACTIVITY    3
#define CHECK_TAINTED_PROCESS   4
#define DEPLOY                  5
#define RETIRE                  6
#define SHOW_RULES              7
#define ADD_RULE                9
#define REM_RULE                8
#define NR_COMMANDS             10



#ifdef __KERNEL__

/*[ADD] The individual curse header includes.*/


/*[ADD] The system curse listing.*/
struct curse_list_entry curse_full_list[] = {
	{	"stub", 0x00000000	},

	{	"sentinel", 0xBADDE5C	}	/*Curse table sentinel. Every entry after this will be ignored.*/
};

/*System call function pointer structure.*/
struct fun_element {
	void (*fun_init)(/*List of arguments*/);
	void (*fun_destroy)(/*List of arguments*/);
	void (*fun_use)(/*List of arguments*/);
};

/*[ADD] The system call function pointer array.*/
struct fun_element fun_array[] = {
	{	NULL, NULL, NULL	},
	
	{	NULL, NULL, NULL	}
};

#endif	/* __KERNEL__ */
