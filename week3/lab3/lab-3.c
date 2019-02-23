#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/slab.h>
#include <asm/current.h>
#include <linux/kfifo.h>
//rbtree example start
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/rbtree.h>
//rbtree example end

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
	struct mytask_struct val_mytask;
	struct mytask_struct *maintask = kmalloc(sizeof(struct mytask_struct), GFP_KERNEL);
	
	printk(KERN_NOTICE "---KFIFO example start---");

	maintask->id = 1;
	maintask->priority = 6;

	print_task(maintask);

	t = kfifo_alloc(&queue, 16, GFP_KERNEL);
	if (t != 0) {
                return;
        }
	//INIT_KFIFO(queue);

	qsize = kfifo_len(&queue);

	printk(KERN_NOTICE "Queue size is %d", qsize);
	printk(KERN_NOTICE "Inserting into queue");

	kfifo_in(&queue, maintask, sizeof(maintask));
	
	qsize = kfifo_len(&queue);

	if (kfifo_is_empty(&queue)) {
		printk(KERN_NOTICE "Queue is empty");
	} else {
		printk(KERN_NOTICE "Queue is not empty, new size is %d", qsize);
	}

	printk(KERN_NOTICE "Polling from queue");

	while(!kfifo_is_empty(&queue)) 
	{
		kfifo_out(&queue, &val_mytask, sizeof(&val_mytask));
		print_task(&val_mytask);
	}

	kfifo_free(&queue);

	printk(KERN_NOTICE "---KFIFO example end---");
}

void navigate_curr_subtree(struct rb_root *root, struct rb_node *node)
{
	int size;
	struct vm_area_struct *vma;

	if(node->rb_left)
		navigate_curr_subtree(root, node->rb_left);
	
	vma = container_of(node, struct vm_area_struct, vm_rb);		
	size = (vma->vm_end - vma->vm_start)/1024;	
	printk("%016lx-%016lx %6uK \n", vma->vm_start, vma->vm_end, size);

	if (node->rb_right) {
		navigate_curr_subtree(root, node->rb_right);
	}
}

void display_virtual_memory(struct task_struct *p)
{
	struct rb_root *root = &p->mm->mm_rb;
	navigate_curr_subtree(root, root->rb_node); 
}

void rbtree_example(void) {
	printk(KERN_NOTICE "---RBTREE example start---");

	display_virtual_memory(current);

	printk(KERN_NOTICE "---RBTREE example end---");
}

int init_module(void) 
{

        printk(KERN_INFO "Lab3: start.\n");
	kfifo_example();
	rbtree_example();
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "Lab3: end.\n");
}
