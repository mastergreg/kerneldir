#include <linux/linkage.h>
asmlinkage long sys_curse (int cmd, int curse_no, pid_t pid) {
	printk(KERN_INFO "Master, you gave me command %d with curse %d on pid %d.\n");
	return (cmd+curse_no+pid);
}
