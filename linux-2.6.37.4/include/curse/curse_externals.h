#ifndef _CURSE_FORWARD_DECLARATIONS
#define _CURSE_FORWARD_DECLARATIONS

/* curse init function */
void curse_init (void);

/* general curse trigger */
void curse_trigger (_Bool defer, curse_id_t cid);

/* fs/read_write.c */
void curse_k_wrapper (void);

/* curse init-destroy wrappers */
void curse_init_actions (struct task_struct *);
void curse_destroy_actions (struct task_struct *);

/* curse allocation interface (for curse private data) */
void *curse_get_alloc (struct task_struct *, size_t);
void curse_free_alloc (struct task_struct *, void *);
//void curse_free_alloced_ll (struct task_struct *);	//This should not be visible to the programmer. Only used in curse_destroy_actions.

#endif	/* _CURSE_FORWARD_DECLARATIONS */
