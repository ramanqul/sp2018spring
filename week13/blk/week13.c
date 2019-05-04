#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/blkdev.h>
#include <linux/fs.h>

#define TAG "Week 13"
#define BLOCK_STORAGE_PATH "/dev/sda1"

static struct block_device *phys_bdev;

struct block_device* read_device(const char *name) {

    struct block_device *bdev;

    bdev = blkdev_get_by_path(name, (fmode_t) 0, (void *)0);
    if (IS_ERR(bdev)) {
        return NULL;
    }

    return bdev;
}


int start(void) {
    pr_info("Starting %s\n", TAG);
    phys_bdev = read_device(BLOCK_STORAGE_PATH);

    if (phys_bdev == NULL) {
        pr_err("Error opening device %s\n", BLOCK_STORAGE_PATH);
        return -EINVAL;
    }

    return 0;
}

void end(void) {
    pr_info("Ending %s\n", TAG);
}

MODULE_LICENSE("GPL");
module_init(start);
module_exit(end);
