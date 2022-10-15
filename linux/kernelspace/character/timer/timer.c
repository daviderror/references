// pri insmode doljen morgnut' odin raz vtechenii 1 sec

#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/jiffies.h>
#include <linux/timer.h>


#define MODULE_LOG_NAME "timer: "



static struct timer_list my_timer;


void timer_callback(struct timer_list *data)
{
    gpio_set_value(4, 0);
}


static int __init timer_init(void) 
{
   
    pr_info(MODULE_LOG_NAME "Hello, Kernel\n");
    
    /* GPIO 4 init */
    if(gpio_request(4, "rpi-gpio-4")) {
        pr_err(MODULE_LOG_NAME "gpio_request failed\n");
        return -1;
    }

    /* Set GPIO 4 direction */
    if(gpio_direction_output(4, 0)) {
        pr_err(MODULE_LOG_NAME "gpio_direction_output failed\n");
        gpio_free(4);
        return -1;
    }


    gpio_set_value(4,1);


    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));



    return 0;
}


static void __exit timer_exit(void) 
{
    gpio_free(4);
    del_timer(&my_timer);
    pr_info(MODULE_LOG_NAME "Goodbye, Kernel\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example timer lkm");
MODULE_VERSION("0.01");

module_init(timer_init);
module_exit(timer_exit);