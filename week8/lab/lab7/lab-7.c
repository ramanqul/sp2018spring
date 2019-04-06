#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

static const char TAG[] = "Lab-7";

struct tasklet_struct my_t;

void tasklet_func(unsigned long data) {
    printk(KERN_INFO "tasklet function is executed");
}

void post_init(void) {
    tasklet_init(&my_t, tasklet_func, 123);
    tasklet_schedule(&my_t);
}

static int __init lab_init(void)
{
    printk(KERN_INFO "%s init", TAG);

    post_init();

    return 0;
}

static void __exit lab_exit(void)
{
  tasklet_kill(&my_t);
  printk(KERN_INFO "%s exit", TAG);
}

module_init(lab_init);
module_exit(lab_exit);
