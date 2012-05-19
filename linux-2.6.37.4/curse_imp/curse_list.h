/*
 * This file is part of the interface between the curses mechanism
 * and the curses implementation.
 * Every curse available must be registered here.
 * TODO: Maybe we could add a description field in each curse.
 * 
 */

#include <stdint.h>

/*Maximum size for a curse name.*/
#define CURSE_MAX_NAME_SIZE 28

/*Curse entry structure for logistic purposes.*/
struct curse_list_entry {
	char curse_name[CURSE_MAX_NAME_SIZE];
	uint64_t curse_id;
};

/*The system curse listing.*/
struct curse_list_entry curse_full_list[] = {
	{	"stub", 0x00000000	},

	{	"sentinel", 0xBADDE5C	}	/*Curse table sentinel. Every entry after this will be ignored.*/
};
