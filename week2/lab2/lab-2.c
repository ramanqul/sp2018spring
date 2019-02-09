#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <asm/current.h>

void print_processes(void) {
	struct task_struct *p, *t;
	printk(KERN_INFO "Begin");

	for_each_process(p) {
		/* this pointlessly prints the name and PID of each task */
		printk(KERN_INFO "%s[%d]\n", p->comm, p->pid);
		for_each_thread(p, t) {
			printk(KERN_INFO "  %s[%d]\n", t->comm, t->pid);
		}
	}

	printk(KERN_INFO "END");
}

int init_module(void)
{

        printk(KERN_INFO "Lab2: start.\n");
	print_processes();

        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "Lab2: end.\n");
}
