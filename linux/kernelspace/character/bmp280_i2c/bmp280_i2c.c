/*
1. nano /boot/config.txt

uncomment:
dtparam=i2c_arm=on 

comment:
dtparam=i2s=on 

2. sudo i2cdetect -y 1
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/kernel.h>


static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define MODULE_NAME "bmp280_i2c"
#define MODULE_CLASS "bmp280_i2c-class"
#define MODULE_LOG_NAME "bmp280_i2c: "


static struct i2c_adapter *bmp280_i2c_adapter = NULL;
static struct i2c_client *bmp280_i2c_client = NULL;

#define I2C_BUS_AVAILABLE      1
#define SLAVE_DEVICE_NAME      "bmp280_i2c_slave"
#define BMP280_SLAVE_ADDRESS   0x76

s32 dig_T1, dig_T2, dig_T3;

static const struct i2c_device_id bmp_id[] = {
    {SLAVE_DEVICE_NAME, 0},
    {}
};

static struct i2c_driver bmp_driver = {
    .driver = {
        .name =  SLAVE_DEVICE_NAME,
        .owner = THIS_MODULE
    }
};


static struct i2c_board_info bmp_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, BMP280_SLAVE_ADDRESS)
};


static s32 read_temperature(void)
{
    int var1, var2;
    s32 raw_temp;
    s32 d1, d2, d3;

    d1 = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xFA);
    d2 = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xFB);
    d3 = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xFC);

    raw_temp = ((d1<<16) | (d2<<8) | d3) >> 4;

    var1 = ((((raw_temp >> 3) - (dig_T1 << 1))) * (dig_T2)) >> 11;

    var2 = (((((raw_temp >> 4) - (dig_T1)) * ((raw_temp >> 4) - (dig_T1))) >> 12) * (dig_T3)) >> 14;
    return ((var1 + var2) *5 +128) >> 8;
}


static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) 
{
    int to_copy, not_copied, delta;

    char out_string[20];
    int temperature;

    to_copy = min(sizeof(out_string), count);
    

    temperature = read_temperature();
    snprintf(out_string, sizeof(out_string), "%d.%d\n", temperature / 10, temperature % 100);

    not_copied = copy_to_user(user_buffer, out_string, to_copy);

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

static int __init bmp280_i2c_init(void) 
{
    u8 id;
    int ret;

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

    bmp280_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

    

    if (NULL != bmp280_i2c_adapter) {
        bmp280_i2c_client = i2c_new_device(bmp280_i2c_adapter, &bmp_i2c_board_info);

        if (NULL != bmp280_i2c_client) {
            if (i2c_add_driver(&bmp_driver) != -1) {
                ret = 0;
            }
            else {
                pr_err(MODULE_LOG_NAME "i2c_add_driver failed!\n");
            }

            i2c_put_adapter(bmp280_i2c_adapter);
        
        }
    }

    pr_info(MODULE_LOG_NAME "bmp280_driver was added\n");

    id = i2c_smbus_read_byte_data(bmp280_i2c_client, 0xD0);
    pr_info(MODULE_LOG_NAME "ID: 0x%x\n", id);

    dig_T1 = i2c_smbus_read_word_data(bmp280_i2c_client, 0x88);
    dig_T2 = i2c_smbus_read_word_data(bmp280_i2c_client, 0x8A);
    dig_T3 = i2c_smbus_read_word_data(bmp280_i2c_client, 0x8C);

    if(dig_T2 > 32767)
        dig_T2 -= 65536;

    if(dig_T3 > 32767)
        dig_T3 -= 65536;

    i2c_smbus_write_byte_data(bmp280_i2c_client, 0xF5, 5 << 5);
    i2c_smbus_write_byte_data(bmp280_i2c_client, 0xF4, (5 << 5)
                                                     | (5 << 2)
                                                     | (3 << 0));

    return ret;

cdev_add_error:
    device_destroy(my_class, my_device_nr);
device_create_error:
    class_destroy(my_class);
class_create_error:
    unregister_chrdev_region(my_device_nr, 1);
    return -1;
}


static void __exit bmp280_i2c_exit(void) 
{
    i2c_unregister_device(bmp280_i2c_client);
    i2c_del_driver(&bmp_driver);

    cdev_del(&my_device);
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    unregister_chrdev_region(my_device_nr, 1);
    pr_info(MODULE_LOG_NAME "Goodbye, Kernel\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example bmp280_i2c lkm");
MODULE_VERSION("0.01");

module_init(bmp280_i2c_init);
module_exit(bmp280_i2c_exit);