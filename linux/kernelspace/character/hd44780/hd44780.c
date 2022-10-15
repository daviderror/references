// echo "SOME MESSEG" > /dev/hd44780

#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/delay.h>

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define MODULE_NAME "hd44780"
#define MODULE_CLASS "hd44780-class"

#define MODULE_LOG_NAME "hd44780: "

static char buffer[17];

unsigned int gpios[] = {
    3, 2, 4, 17, 27, 22, 10, 9, 11, 5
};

#define ENABLE_PIN        gpios[0]
#define REGISTER_SELECT   gpios[1]


static void lcd_enable(void) 
{
    gpio_set_value(ENABLE_PIN, 1);
    msleep(5);
    gpio_set_value(ENABLE_PIN, 0);
}


static void lcd_send_byte(char data) 
{
    int i;

    for (i = 0; i < 8; i ++) {
        gpio_set_value(gpios[i + 2], ((data) & (1 << i) >> i));
    }

    lcd_enable();
    msleep(5);
}


static void lcd_command(char data) 
{
    gpio_set_value(REGISTER_SELECT, 0);

    lcd_send_byte(data);
}


static void lcd_data(char data) 
{
    gpio_set_value(REGISTER_SELECT, 1);

    lcd_send_byte(data);
}


static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) 
{
    int to_copy, not_copied, delta, i;

    to_copy = min(count, sizeof(buffer));
    not_copied = copy_from_user(buffer, user_buffer, to_copy);

    delta = to_copy - not_copied;

    lcd_command(0x1);

    for (i = 0; i < to_copy; i++) {
        lcd_data(buffer[i]);
    }

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

static int __init hd44780_init(void) 
{
    int i;
    char *names[] = {"ENABLE_PIN", "REGISTER_SELECT", "DATA_PIN0", "DATA_PIN1", "DATA_PIN2", "DATA_PIN3", "DATA_PIN4", "DATA_PIN5", "DATA_PIN6", "DATA_PIN7"};


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

    for (i = 0; i < 10; i++) {
        if (gpio_request(gpios[i], names[i])) {
            pr_err(MODULE_LOG_NAME "gpio_request failed!\n");
            goto gpio_request_error;
        }
    }

    for (i = 0; i < 10; i++) {
        if (gpio_direction_output(gpios[i], 0)) {
            pr_err(MODULE_LOG_NAME "gpio_direction_output failed!\n");
            goto gpio_request_error;
        }
    }


    lcd_command(0x30);
    lcd_command(0xf);
    lcd_command(0x1);

    char hello_text[] = "Hello world";

    for (i = 0; i < sizeof (hello_text); i++) {
        gpio_set_value(hello_text[i]);  
    }


    return 0;

gpio_request_error:
    for (i = 9; i >= 0; i--) {
        gpio_free(gpios[i]);  
    }
cdev_add_error:
    device_destroy(my_class, my_device_nr);
device_create_error:
    class_destroy(my_class);
class_create_error:
    unregister_chrdev_region(my_device_nr, 1);
    return -1;
}


static void __exit hd44780_exit(void) 
{
    int i;

    lcd_command(0x1);

    for (i = 0; i < 10; i++) {
        gpio_set_value(gpios[i], 0);
        gpio_free(gpios[i]);  
    }

    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev_region(my_device_nr, 1);
    pr_info(MODULE_LOG_NAME "Goodbye, Kernel\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example hd44780 lkm");
MODULE_VERSION("0.01");

module_init(hd44780_init);
module_exit(hd44780_exit);
