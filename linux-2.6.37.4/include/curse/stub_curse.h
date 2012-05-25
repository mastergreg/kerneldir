#ifndef _STUB_CURSE
#define _STUB_CURSE

static inline void stub_init(void /*or not*/) {
    printk("Open of curse initiated\n");
	return;
}
static inline void stub_destroy(void /*or not*/) {
    printk("Close of curse initiated\n");
    return;
}
static inline void stub_inject(void /*not*/) {
    printk("Run of curse initiated\n");
    return;
}

#endif
