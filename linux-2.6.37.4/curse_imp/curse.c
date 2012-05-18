#include <linux/linkage.h>
asmlinkage long sys_curse (int cmd, int curse_no) {
	printk(KERN_INFO "Master, you gave me command %d on curse %d.\n");
	return (cmd+curse_no);
}
