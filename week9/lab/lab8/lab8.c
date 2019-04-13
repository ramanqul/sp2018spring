#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/random.h>
#define TAG "Lab8"
#define MAX_NUM 1000000

int gen_int(void) {
    int n;
    get_random_bytes(&n, sizeof(n));
    n = n < 0 ? n * -1 : n;
    n = n % MAX_NUM;
    return n;
}

void createThreads(void) {
    int n; 
    n = gen_int();
    if (printk_ratelimit()) {
       printk(KERN_INFO "random number is %d\n", n);
    }
}

int init_module(void)
{

        printk(KERN_INFO "START %s\n", TAG);
        createThreads();
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_DEBUG "END %s\n", TAG);
}
