#ifndef _CURSE_FORWARD_DECLARATIONS
#define _CURSE_FORWARD_DECLARATIONS

/* curse init function */
#ifndef CONFIG_CURSES
#define CONFIG_CURSES
#endif
void curse_init (void);

/* general curse trigger */
//inline void curse_trigger_checkpoint ();

/* fs/read_write.c */
inline void curse_k_wrapper (void);

#endif	/* _CURSE_FORWARD_DECLARATIONS */
