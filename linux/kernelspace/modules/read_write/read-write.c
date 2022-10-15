#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define MODULE_NAME "read-write"
#define MODULE_CLASS_NAME "read-write-class"
#define MODULE_LOG_NAME "read-write: "

static char buffer[255];
static int buffer_pointer;


static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;


static ssize_t driver_read(struct file *p_file, char *p_user_buffer, size_t count, loff_t *offs)
{
    int to_copy, not_copied, delta;

    to_copy = min(count, buffer_pointer);

    not_copied = copy_to_user(p_user_buffer, buffer, to_copy);

    delta = to_copy - not_copied;

    return delta;

}


static ssize_t driver_write(struct file *p_file, const char *p_user_buffer, size_t count, loff_t *offs)
{
    int to_copy, not_copied, delta;

    to_copy = min(count, sizeof (buffer));

    not_copied = copy_from_user(buffer, p_user_buffer, to_copy);
    buffer_pointer = to_copy;

    delta = to_copy - not_copied;

    return delta;

}


static int driver_open(struct inode *device_file, struct file *instance)
{
    pr_info(MODULE_LOG_NAME "opened\n");

    return 0;
}


static int driver_close(struct inode *device_file, struct file *instance)
{
    pr_info(MODULE_LOG_NAME "closed\n");

    return 0;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write
};



static int __init read_write_init(void) 
{ 
    int status = 0;

    if (alloc_chrdev_region(&my_device_nr, 0, 1, MODULE_NAME) < 0) {
        pr_err(MODULE_LOG_NAME "alloc_chrdev_region failed");
        return -1;
    }

    pr_info(MODULE_LOG_NAME "Major: %d, Minor: %d\n", 
        my_device_nr >> 20, my_device_nr & 0xfffff);

    if ((my_class = class_create(THIS_MODULE, MODULE_CLASS_NAME)) == NULL) {
        pr_err(MODULE_LOG_NAME "class_create failed");
        goto class_create_error;
    }


    if (device_create(my_class, NULL, my_device_nr, NULL,MODULE_NAME) == NULL) {
        pr_err(MODULE_LOG_NAME "device_create failed");
        goto device_create_error;
    }


    cdev_init(&my_device, &fops);


    if (cdev_add(&my_device, my_device_nr, 1) == -1) {
        pr_err(MODULE_LOG_NAME "cdev_add failed");
        goto cdev_add_error;
    }


    return 0; 

cdev_add_error:
    device_destroy(my_class, my_device_nr);

device_create_error:
    class_destroy(my_class);

class_create_error:
    unregister_chrdev(my_device_nr, 1);

    return -1;
} 


static void __exit read_write_exit(void) 
{ 
    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev(my_device_nr, 1);
    pr_info(MODULE_LOG_NAME "Goodbye, kernel!\n");
} 



MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example read-write lkm.");
MODULE_VERSION("0.01");

module_init(read_write_init); 
module_exit(read_write_exit);