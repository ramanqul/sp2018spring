#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <linux/fdtable.h>
#include <linux/nsproxy.h>
#include <linux/dcache.h>

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define TAG "Week 12"

static int pid = 1;
module_param(pid, int, 0644);

void list_used_files(struct task_struct *task) {
    int i=0;
    struct fdtable *files_table;
    struct path files_path;
    char *cwd;
    char buf[100];

    files_table = files_fdtable(task->files);

    if (!files_table || !files_table->fd) {
        printk(KERN_INFO "files_table empty!/n");
        return;
    }

    while(files_table->fd[i] != NULL) {
        files_path = files_table->fd[i]->f_path;
        cwd = d_path(&files_path, buf, 100 * sizeof(char));
        printk(KERN_INFO "Open file with fd %d  %s", i, cwd);
        i++;
    }
}


void fs1(void) {
    struct task_struct *cur_proc;
    unsigned long used_files_cnt = 0;
    struct pid *proc_pid;
    struct task_struct *proc_task;

    cur_proc = current;
    printk(KERN_INFO "Process ID is %d\n", cur_proc->pid);
    printk(KERN_INFO "Process name %s\n", cur_proc->comm);

    printk(KERN_INFO "Process fs pointer: %p\n", cur_proc->fs);
    printk(KERN_INFO "Process files pointer: %p\n", cur_proc->files);
    printk(KERN_INFO "Process nsproxy pointer: %p\n", cur_proc->nsproxy);

    used_files_cnt = *cur_proc->files->fdt->open_fds;

    printk(KERN_INFO "Files used: %ld\n", used_files_cnt);

    proc_pid = find_vpid(pid);
    proc_task = pid_task(proc_pid, PIDTYPE_PID);

    list_used_files(proc_task);
}


MODULE_LICENSE("GPL");

int init_module(void) {
   printk(KERN_INFO "Starting %s\n", TAG);
   fs1();
   return 0;
}

void cleanup_module(void) {
   printk(KERN_INFO "Cleanup %s\n", TAG);
}
