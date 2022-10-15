#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define MODULE_NAME "button"
#define MODULE_CLASS "button-class"

#define MODULE_LOG_NAME "button-lkm: "

static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) 
{
    int to_copy, not_copied, delta;
    char value[3] = " \n";

    to_copy = min(count, sizeof(value));
    
    value[0] = gpio_get_value(17) + '0';
    not_copied = copy_to_user(user_buffer, &value, to_copy);

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
    .read = driver_read
};

static int __init button_init(void) 
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

    /* GPIO 17 init */
    if(gpio_request(17, "rpi-gpio-17")) {
        pr_err("gpio_request failed\n");
        goto gpio_direction_input_error;
    }

    /* Set GPIO 17 direction */
    if(gpio_direction_input(17)) {
        pr_err("gpio_direction_input failed\n");
        goto gpio_direction_input_error;
    }


    return 0;

gpio_direction_input_error:
    gpio_free(17);
cdev_add_error:
    device_destroy(my_class, my_device_nr);
device_create_error:
    class_destroy(my_class);
class_create_error:
    unregister_chrdev_region(my_device_nr, 1);
    return -1;
}


static void __exit button_exit(void) 
{
    gpio_free(17);
    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev_region(my_device_nr, 1);
    pr_info(MODULE_LOG_NAME "Goodbye, Kernel\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example button lkm");
MODULE_VERSION("0.01");

module_init(button_init);
module_exit(button_exit);