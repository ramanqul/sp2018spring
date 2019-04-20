#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>
#include <linux/types.h>

#define TAG "week 11"

MODULE_LICENSE("GPL");

struct page* mypages;

void pageLevelAllocation(void) {
   mypages = alloc_pages(0, 2); //2^2 = 4 pages will be allocated
}


int init_module(void) {
   printk(KERN_INFO "Starting %s\n", TAG);
   pageLevelAllocation();
   return 0;
}

void cleanup_module(void) {
   printk(KERN_INFO "Cleanup %s\n", TAG);
   free_pages(mypages, 2);
}


