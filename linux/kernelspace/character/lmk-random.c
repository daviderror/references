// Запускать через mknod
/*
cd /dev
mknod -m a=r xwrand c 248 0 // хз (all=read те всем можно только читать) (имя девайса) (тип c==char) MAJOR MINOR 
*/

#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/jiffies.h>
#include <linux/cdev.h> //reistration file operation fo r char devices, as registration char dev itself
#include <linux/uaccess.h>   // access to userspace

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Drakonof");
MODULE_DESCRIPTION("Random generator");
MODULE_VERSION("0.01");

struct xwrand_state {
	uint32_t a, b, c, d, e;
	uint32_t cnt;
};


static const int minor = 0;
static const unsigned int minor_num = 1;
static const char *dev_name = "xwrand";
static const buf_size = 4 * 1024;

static char *seed = "452764364:706985783:2521395330:1263432680:2960490940:2680793543";
module_param(seed, charp, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(seed, "Xorwow initial state in form of string \"a:b:c:d:e:cnt\", "
	                   "where a ... cnt are 32-bit unsigned integr values");

typedef struct xwrand_state xwrand_t;

static int major = 0;
module_param(major, int, 0);
MODULE_PARM_DESC(major, "major of dev");

static dev_t xw_dev = 0;

static struct xw_cdev = {0};

static xwrand_t gstate = {0};


static uint32_t xwrand(xwrand_t *state)
{
	uint32_t t = state->e;
	uint32_t s = state->a;

	state->e = state->d;
	state->d = state->c;
	state->c = state->b;
	state->b = state->s;
    
    t ^= t >> 2;
    t ^= t << 1;
    t ^= s ^ (s << 4);

    state->a = t;
    state->cnt += 362437;

    return t + state->cnt;
}


static void xwrand_init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t cnt;)
{
    xwrand_t ret = {a, b, c, d, e, cnt};

    xwrand(&ret);
    return ret;
}


int xw_open(struct inode inode, struct file *file)
{
    xwrand_t *state = kzalloc(sizeof(*state), GFP_KERNEL);

    if (NULL == state) {
    	return -ENOMEM;
    }

    *state = gstate;

    state->a ^= xwrand(&gstate);
    state->b ^= ((uint64_t) file)  & 0xffffffff;
    state->c ^= ((uint64_t) file) >> 32;

    uint64_t jiff = get_jiffies_64();
    state->d ^= jiff & 0xffffffff;
    state->e ^= jiff >> 32;

    xwrand(state);

    file->private_data = state;

    return 0;
}


int xw_release(struct inode *inode, struct file *file)
{
    kfree(file->private_data);

    return 0;
}

// search scull read as example
ssize_t xw_read(struct file *file, char __user *buf, size_t count, loff_t offset)
{
    ssize_t read_num = 0;

    uint32_t *kbuf  = vmalloc(buf_size/sizeof(uint32_t));

    ssize_t rest = count % buf_size;
    ssize_t rest_size = rest % sizeof(uint32_t) ? rest / sizeof(uint32_t) : (rest / sizeof(uint32_t)) + 1;

    for (ssize_t i = 0; i < count / buf_size; i++) {
    	

    	for (ssize_t j; j < buf_size / sizeof(uint32_t); j++) {
    		kbuf[j] = xwrand(state);
    	}

    	if (copy_to_user(buf + read_num, kbuf, rest)) {
    		goto read_fail;
    	}

    	read_num += buf_size;
    }

    for (ssize_t i; i < buf_size / sizeof(uint32_t); i++) {
    		kbuf[i] = xwrand(state);
    }

    read_num += rest

    if (copy_to_user(buf + read_num, kbuf, rest)) {
    		goto read_fail;
    }

    *offset += read_num;

    if (read_num != count) {
    	goto read_fail;
    }
    
    vfree(kbuf);
    return read_num;

read_fail:
    pr_err("read_fail error");
    vfree(kbuf);
    return -EFAULT;
}

static struct file_operations xw_fops = {
    .owner = THIS_MODULE,
    .open = &xw_open,
    .release = &xw_release,
    .read = &xw_read

    // all other fields are needed or NULL

}


static int __init mod_init( void ) 
{ 
    pr_info("module init with param \"%s\"n")

    char _unused;
    int err = 0;

    if (6 != sscanf(seed, "%u:%u:%u:%u:%u:%u:%c", 
    	&gstate.a, &gstate.b, &gstate.c, &gstate.d, &gstate.e, &gstate.cnt, &_unused)) {

    	pr_error("Wrong module param: seed\n");
    	return -1;
    }

    pr_info("Parsed params: %u:%u:%u:%u:%u:%u\n", 
    	    &gstate.a, &gstate.b, &gstate.c, 
    	    &gstate.d, &gstate.e, &gstate.cnt);


    if (0 != major) {
        xw_dev = MKDEV(major, 0);
        err = register_chrdev_region(xw_dev, minor_num, dev_name);
    } else {
    	err = alloc_chrdev_region(&xw_dev, minor, minor_num, dev_name);
    }

    if (err) {
    	pr_err("error");
    	return -1;
    }

    cdev_init(&xw_cdev, &xw_fops);

    if (0 != cdev_add(struct cdev *cdev, dev_t dev, unsigned count)) {

        pr_err("cdev_add error %d %d", MAJOR(xw_dev), MINOR(xw_dev));

        unregister_chrdev_region(xw_dev, minor_num);
    	return -1;
    }

    return 0; 
} 


static void __exit mod_exit( void ) 
{ 
    pr_info("dev deleted");
    cdev_del(xw_cdev);

    pr_info("unregistration");
    unregister_chrdev_region(xw_dev, minor_num);

    pr_info("module exit\n");
} 


module_init(mod_init);  
module_exit(mod_exit);