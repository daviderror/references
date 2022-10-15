/*
sudo insmod pwm.ko
sudo chmod 666 /dev/pwm
echo 3 > /dev/pwm
echo a > /dev/pwm
echo j > /dev/pwm
echo b > /dev/pwm
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/pwm.h>

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define MODULE_NAME "pwm"
#define MODULE_CLASS "pwm-class"
#define MODULE_LOG_NAME "pwm: "


struct pwm_device *pwm0 = NULL;

u32 pwm_on_time = 50000000;


static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) 
{
    int to_copy, not_copied, delta;

    char value;

    to_copy = min(count, sizeof(value));
    not_copied = copy_from_user(&value, user_buffer, to_copy);

    if (value < 'a' || value > 'j') {
        pr_err(MODULE_LOG_NAME "invalid value\n");
    }
    else {
        pwm_config(pwm0, 1000000000 * (value - 'a'), 1000000000);
    }


    delta = to_copy - not_copied;

    return delta;
}

static int driver_open(struct inode *device_file, struct file *instance) 
{
    pr_info(MODULE_LOG_NAME "open was called!\n");
    return 0;
}


static int driver_close(struct inode *device_file, struct file *instance) 
{
    pr_info(MODULE_LOG_NAME "close was called!\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .write = driver_write
};

static int __init pwm0_init(void) 
{
    /* Allocate a device nr */
    if( alloc_chrdev_region(&my_device_nr, 0, 1, MODULE_NAME) < 0) {
        pr_err(MODULE_LOG_NAME "alloc_chrdev_region failed\n");
        return -1;
    }
    
    pr_info(MODULE_LOG_NAME "Major: %d, Minor: %d\n", my_device_nr >> 20, my_device_nr && 0xfffff);

    /* Create device class */
    if((my_class = class_create(THIS_MODULE, MODULE_CLASS)) == NULL) {
        pr_err(MODULE_LOG_NAME "class_create failed\n");
        goto class_create_error;
    }

    /* create device file */
    if(device_create(my_class, NULL, my_device_nr, NULL, MODULE_NAME) == NULL) {
        pr_err(MODULE_LOG_NAME "device_create failed\n");
        goto device_create_error;
    }

    /* Initialize device file */
    cdev_init(&my_device, &fops);

    /* Regisering device to kernel */
    if(cdev_add(&my_device, my_device_nr, 1) == -1) {
        pr_err(MODULE_LOG_NAME "cdev_add failed!\n");
        goto cdev_add_error;
    }

    pwm0 = pwm_request(0, "my-pwm");

    if (NULL == pwm0) {
        pr_err(MODULE_LOG_NAME "pwm_request failed!\n");
        goto pwm_request_error;
    }

    pwm_config(pwm0, pwm_on_time, 1000000000);
    pwm_enable(pwm0);

    return 0;

pwm_request_error:
    pwm_disable(pwm0);
    pwm_free(pwm0);
cdev_add_error:
    device_destroy(my_class, my_device_nr);
device_create_error:
    class_destroy(my_class);
class_create_error:
    unregister_chrdev_region(my_device_nr, 1);
    return -1;
}


static void __exit pwm0_exit(void) 
{
    pwm_disable(pwm0);
    pwm_free(pwm0);

    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev_region(my_device_nr, 1);
    pr_info(MODULE_LOG_NAME "Goodbye, Kernel\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example pwm lkm");
MODULE_VERSION("0.01");

module_init(pwm0_init);
module_exit(pwm0_exit);