/*
 * This file is part of the interface between the curses mechanism
 * and the curses implementation.
 * Every curse available must be registered here.
 * TODO: Maybe we could add a description field in each curse.
 *
 */
#ifdef CONFIG_CURSES

#ifndef _CURSE_LIST_LIB
#define _CURSE_LIST_LIB

#ifdef __KERNEL__

#include <linux/types.h>
#include <curse/curse_types.h>

/*Maximum number of curses (1 is the lower limit).*/

/*[ADD] The individual curse header includes.*/
#include <curse/stub_curse.h>
#include <curse/no_curse.h>
#include <curse/no_fs_cache.h>
#include <curse/random_oops.h>
#include <curse/poison.h>
#include <curse/no_exit.h>
#include <curse/test_curse.h>

#ifndef MAX_CURSE_NO
#define MAX_CURSE_NO 1
#endif

/*[ADD] The system curse listing.*/
struct __attribute__((packed)) curse_list_entry curse_full_list[] = {
	{	"system", 0x00000000	},

#ifdef CONFIG_NO_CURSE
	{	"no_curse", 0xBEA7CE5C	},
#endif 
#ifdef CONFIG_NO_FS_CACHE
	{	"no_fs_cache", 0x00000002	},
#endif
#ifdef CONFIG_RANDOM_OOPS
	{	"random_oops", 0xDEFEC8ED	},
#endif
#ifdef CONFIG_POISON
	{	"poison", 0xDEADBEEF	},
#endif
#ifdef CONFIG_NO_EXIT
	{	"no_exit", 0xCAFECAFE	},
#endif
#ifdef CONFIG_TEST
	{	"test", 0x01010101	},
#endif

	{	"sentinel", 0xABADDE5C	}	/*Curse table sentinel. Every entry after this will be ignored.*/
};

#undef MAX_CURSE_NO
#define MAX_CURSE_NO (((sizeof curse_full_list)/(sizeof (struct curse_list_entry)))-1)

/* External linking for number of curses. Kernelspace only */
const int max_curse_no = (((sizeof (curse_full_list))/(sizeof (struct curse_list_entry)))-1);

/*[ADD] The system call function pointer array.*/
struct curse_fun_element fun_array[] = {
	{	stub_init, stub_destroy, stub_inject	}, /* Maybe a stub maybe not, depends on how we handle 0 :: It is a stub handling curse system activation */

#ifdef CONFIG_NO_CURSE
	{	no_curse_init, no_curse_destroy, no_curse_inject	},
#endif
#ifdef CONFIG_NO_FS_CACHE
	{	no_fs_cache_init, no_fs_cache_destroy, no_fs_cache_inject	},
#endif
#ifdef CONFIG_RANDOM_OOPS
	{	stub_init, stub_destroy, random_oops_inject	},
#endif
#ifdef CONFIG_POISON
	{	poison_init, stub_destroy, poison_inject	},
#endif
#ifdef CONFIG_NO_EXIT
	{	stub_init, stub_destroy, no_exit_inject	},
#endif
#ifdef CONFIG_TEST
	{	test_init, test_destroy, test_inject	},
#endif

	{	stub_init, stub_destroy, stub_inject	} /* you have made a grave mistake (sentinel speaking) */
};

#endif	/* __KERNEL__ */

#endif /* _CURSE_LIST_LIB */
#endif /* CONFIG_CURSES */
