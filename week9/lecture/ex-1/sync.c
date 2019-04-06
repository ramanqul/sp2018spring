#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

#define TAG "week9" 
#define DELAY 100

static struct task_struct *t1;
static struct task_struct *t2;
static struct task_struct *t3;
static struct task_struct *t4;
static struct task_struct *t5;

DEFINE_SPINLOCK(lock);

static int counter = 0;

static int threadMethod(void *unused) {
    int i = 0;
    spin_lock(&lock);
    int local_counter = counter; //read shared data
/*	
    if (strcmp(current->comm, "mythread1") == 0) {
 	msleep(2);
    } else {
        msleep(1);
    }
*/
    for (i=0;i<5;i++) {
       printk(KERN_INFO "I'm %s, counter: %d", current->comm, local_counter);
       udelay(DELAY);
       local_counter++; //update 
    }
    
    counter = local_counter; //store back
    spin_unlock(&lock);

    return 0;
}

void createThreads(void) {
        t1 = kthread_run(threadMethod, NULL, "mythread1");
        t2 = kthread_run(threadMethod, NULL, "mythread2");
        t3 = kthread_run(threadMethod, NULL, "mythread3");
        t4 = kthread_run(threadMethod, NULL, "mythread4");
        t5 = kthread_run(threadMethod, NULL, "mythread5");

	//kthread_stop(t1);
	//kthread_stop(t2);
}

int init_module(void)
{

        printk(KERN_INFO "START %s\n", TAG);
        createThreads();
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "END %s\n", TAG);
}
