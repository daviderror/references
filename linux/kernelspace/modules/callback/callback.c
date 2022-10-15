#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/fs.h>


#define MODULE_LOG_NAME "callback: "
#define MODULE_NAME     "callback"
#define MY_MAJOR        90U


static int driver_open(struct inode *p_device_file, struct file *p_instance)
{
    pr_info(MODULE_LOG_NAME "- open was called!\n");
    
    return 0;
}


static int driver_close(struct inode *p_device_file, struct file *p_instance)
{
   pr_info(MODULE_LOG_NAME "- close was called!\n");
    
    return 0;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close
};


static int __init callback_init(void) 
{ 
    int status = 0;

    status = register_chrdev(MY_MAJOR, MODULE_NAME, &fops);

    if (0 == status) {
        pr_info(MODULE_LOG_NAME "Dev major: %d, minor: %d\n", MY_MAJOR, 0);
    }
    else if (status > 0) {
        pr_info(MODULE_LOG_NAME "Dev major: %d, minor: %d\n", status >> 20, status&0xfffff);
    }
    else {
        pr_err(MODULE_LOG_NAME "Couldn't register device number\n");
        return -1;
    } 

    return 0; 
} 


static void __exit callback_exit(void) 
{ 

    unregister_chrdev(MY_MAJOR, MODULE_NAME);
    pr_info(MODULE_LOG_NAME "Goodbye, kernel!\n");
} 


MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example callback lkm.");
MODULE_VERSION("0.01");

module_init(callback_init); 
module_exit(callback_exit);