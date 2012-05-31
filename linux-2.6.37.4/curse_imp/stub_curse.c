#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>

#include <curse/stub_curse.h>

void stub_init (struct task_struct * target) {
    printk("Open of curse initiated\n");
	return;
}

 void stub_destroy (struct task_struct * target) {
    printk("Close of curse initiated\n");
    return;
}

void stub_inject (uint64_t mask) {
    printk("Run of curse initiated\n");
    return;
}
