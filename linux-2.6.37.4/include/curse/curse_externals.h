#ifndef _CURSE_FORWARD_DECLARATIONS
#define _CURSE_FORWARD_DECLARATIONS

#ifndef CONFIG_CURSES
#define CONFIG_CURSES
#endif

/* curse init function */
void curse_init (void);

/* general curse trigger */
void curse_trigger (_Bool defer, curse_id_t cid);

/* fs/read_write.c */
void curse_k_wrapper (void);

/* curse init-destroy wrappers */
void curse_init_actions (struct task_struct *);
void curse_destroy_actions (struct task_struct *);

#endif	/* _CURSE_FORWARD_DECLARATIONS */
