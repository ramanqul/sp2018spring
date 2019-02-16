#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/smp.h>

/*
Challedge: find total number of cpu cores
*/
void print_total_cpu(void) {
	printk(KERN_INFO, "Challendge: total cpus are %d", total_cpus);
}


int init_module(void)
{
	printk(KERN_INFO "Lab 1: start.\n");

	printk(KERN_INFO "Begin");
	print_total_cpu();
	printk(KERN_INFO "End");

	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Lab 1: end.\n");
}
