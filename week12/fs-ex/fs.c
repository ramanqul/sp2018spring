#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <linux/fdtable.h>
#include <linux/nsproxy.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>

#define TAG "Week 12"


void fs1(void) {
    struct task_struct *cur_proc;
    int used_files_cnt = 0;

    cur_proc = current;
    printk(KERN_INFO "Process ID is %d\n", cur_proc->pid);
    printk(KERN_INFO "Process name %s\n", cur_proc->comm);

    printk(KERN_INFO "Process fs pointer: %p\n", cur_proc->fs);
    printk(KERN_INFO "Process files pointer: %p\n", cur_proc->files);
    printk(KERN_INFO "Process nsproxy pointer: %p\n", cur_proc->nsproxy);

    used_files_cnt = cur_proc->files->count.counter;

    printk(KERN_INFO "Files used: %d\n", used_files_cnt);
}


int init_module(void) {
   printk(KERN_INFO "Starting %s\n", TAG);
   fs1();
   return 0;
}

void cleanup_module(void) {
   printk(KERN_INFO "Cleanup %s\n", TAG);
}
