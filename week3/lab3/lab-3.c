#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/slab.h>
#include <linux/kfifo.h>

struct mytask_struct {
	int id;
	int priority : 5;
};

void print_task(struct mytask_struct* t) 
{
	printk(KERN_NOTICE "Task(%d) has priority %d\n", t->id, t->priority);
}

void kfifo_example(void) {
	int t;
	int qsize;
	struct kfifo queue;
	struct mytask_struct *val_mytask;
	struct mytask_struct *maintask = kmalloc(sizeof(struct mytask_struct), GFP_KERNEL);

	maintask->id = 1;
	maintask->priority = 6;

	print_task(maintask);

	//t = kfifo_alloc(&queue, 16, GFP_KERNEL);
	INIT_KFIFO(queue);

	qsize = kfifo_len(&queue);

	printk(KERN_NOTICE "Queue size is %d", qsize);

	/*it can't allocate kfifo may be because of memory shortage*/
	if (t) {
		return;
	}

	printk(KERN_NOTICE "Inserting into queue");

	kfifo_in(&queue, maintask, sizeof(maintask));
	
	qsize = kfifo_len(&queue);

	if (kfifo_is_empty(&queue)) {
		printk(KERN_NOTICE "Queue is empty");
	} else {
		printk(KERN_NOTICE "Queue is not empty, new size is %d", qsize);
	}

	printk(KERN_NOTICE "Peek from queue");

	t = kfifo_out(&queue, val_mytask, sizeof(struct mytask_struct));

	if (t > 0) {
		printk("Nothing was peeked from queue");
	} else {
		if (val_mytask != NULL) {
			print_task(val_mytask);
		}
	}

	kfifo_free(&queue);
}


int init_module(void) 
{

        printk(KERN_INFO "Lab3: start.\n");
	kfifo_example();
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "Lab3: end.\n");
}
