#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>

#include <curse/stub_curse.h>

void stub_init (void /*or not*/) {
    printk("Open of curse initiated\n");
	return;
}

void stub_destroy (void /*or not*/) {
    printk("Close of curse initiated\n");
    return;
}

void stub_inject (void /*not*/) {
    printk("Run of curse initiated\n");
    return;
}

