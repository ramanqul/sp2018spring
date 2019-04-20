#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>
#include <linux/types.h>
#include <linux/time.h>

#define TAG "week 11"

MODULE_LICENSE("GPL");

struct page* mypages;

void pageLevelAllocation(void) {
   struct timespec t1, t2; 
   int page_order = 2;
   getnstimeofday(&t1);
   mypages = alloc_pages(GFP_KERNEL, page_order); //2^2 = 4 pages will be allocated
   __free_pages(mypages, page_order);
   getnstimeofday(&t2);
   printk(KERN_INFO "%s time required is %ld\n", TAG, t2.tv_nsec - t1.tv_nsec);
}


int init_module(void) {
   printk(KERN_INFO "Starting %s\n", TAG);
   pageLevelAllocation();
   return 0;
}

void cleanup_module(void) {
   printk(KERN_INFO "Cleanup %s\n", TAG);
}


