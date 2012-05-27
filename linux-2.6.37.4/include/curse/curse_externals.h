#ifndef _CURSE_FORWARD_DECLARATIONS
#define _CURSE_FORWARD_DECLARATIONS

#ifndef CONFIG_CURSES
#define CONFIG_CURSES
#endif

/* curse init function */
void curse_init (void);

//typedef curse_id_t;

/* general curse trigger */
inline void curse_trigger (curse_id_t cid);

/* fs/read_write.c */
inline void curse_k_wrapper (void);

#endif	/* _CURSE_FORWARD_DECLARATIONS */
