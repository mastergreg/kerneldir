#ifndef _CURSE_FORWARD_DECLARATIONS
#define _CURSE_FORWARD_DECLARATIONS

#ifndef CONFIG_CURSES
#define CONFIG_CURSES
#endif
/* curse init function */
void curse_init (void);

/* general curse trigger */
//inline void curse_trigger ();

/* fs/read_write.c */
inline void curse_k_wrapper (void);

#endif	/* _CURSE_FORWARD_DECLARATIONS */
