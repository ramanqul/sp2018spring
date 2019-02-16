#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/list.h>
#include <linux/slab.h>


struct person_struct {
	char* name;
	int age;
	struct list_head list;
};


static void list_example(void) {
        int i;

        struct person_struct *parent = kmalloc(sizeof(struct person_struct), GFP_KERNEL);
        struct person_struct *val;


        parent->name = "Week3 example";
        parent->age = 1;

        INIT_LIST_HEAD(&parent->list);

        for (i=0;i<10;i++) {
		struct person_struct *fp = kmalloc(sizeof(struct person_struct), GFP_KERNEL);
		fp->name = "Loop";
		fp->age = i;

		list_add_tail(&(fp->list), &parent->list);
		printk(KERN_INFO "Item %d was added to tail of the list\n", i+1);
	}


	list_for_each_entry(val, &parent->list, list) {
		printk(KERN_INFO "Person from list: name=%s, age=%d\n", val->name, val->age);
	}
}


int init_module(void)
{

	printk("START\n");
	list_example();
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Week3: goodbye.\n");
}
