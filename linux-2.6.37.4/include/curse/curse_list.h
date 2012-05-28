/*
 * This file is part of the interface between the curses mechanism
 * and the curses implementation.
 * Every curse available must be registered here.
 * TODO: Maybe we could add a description field in each curse.
 * 
 */

#ifndef _CURSE_LIST_LIB
#define _CURSE_LIST_LIB

#ifdef __KERNEL__

#include <linux/types.h>
#include <curse/curse_types.h>

/*Maximum number of curses (1 is the lower limit).*/
#ifndef MAX_CURSE_NO
#define MAX_CURSE_NO 1
#endif

/*[ADD] The individual curse header includes.*/
#include <curse/no_curse.h>
#include <curse/no_fs_cache.h>
#include <curse/stub_curse.h>

/*[ADD] The system curse listing.*/
struct curse_list_entry curse_full_list[] = {
	{	"stub", 0x00000000	},
	
	{	"no_curse", 0xBEA7CE5C	},
	{	"no_fs_cache", 0x00000002	},
	
	{	"sentinel", 0xABADDE5C	}	/*Curse table sentinel. Every entry after this will be ignored.*/
};

#undef MAX_CURSE_NO
#define MAX_CURSE_NO (((sizeof curse_full_list)/(sizeof (struct curse_list_entry)))-1)

/* External linking for number of curses. */
const int max_curse_no = (((sizeof (curse_full_list))/(sizeof (struct curse_list_entry)))-1);

/*[ADD] The system call function pointer array.*/
struct curse_fun_element fun_array[] = {
	{	stub_init, stub_destroy, stub_inject	}, /* Maybe a stub maybe not, depends on how we handle 0 :: It is a stub handling curse system activation */

	{	stub_init, stub_destroy, no_curse_inject	},
	{	no_fs_cache_init, no_fs_cache_destroy, no_fs_cache_inject	},

	{	stub_init, stub_destroy, stub_inject	} /* you have made a grave mistake (sentinel speaking) */
};

#endif	/* __KERNEL__ */

#endif /* _CURSE_LIST_LIB */
