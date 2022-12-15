// pri insmode doljen morgnut' odin raz vtechenii 1 sec

#include <linux/module.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include <linux/jiffies.h>


#define MODULE_LOG_NAME "hr_timer: "



static struct hrtimer my_hr_timer;

u64 start_t;

static enum hrtimer_restart test_hrtimer_handler(struct hrtimer *timer)
{
    u64 now_t = jiffies;

    pr_info(MODULE_LOG_NAME "start_t - now_t = %u\n", 
            jiffies_to_msecs(now_t - start_t));

    return HRTIMER_NORESTART;
}


static int __init hr_timer_init(void) 
{
   
    pr_info(MODULE_LOG_NAME "Hello, Kernel\n");
    
    hrtimer_init(&my_hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    my_hr_timer.function = &test_hrtimer_handler;
    start_t = jiffies;
    hrtimer_start(&my_hr_timer, ms_to_ktime(100), HRTIMER_MODE_REL);

    return 0;
}


static void __exit hr_timer_exit(void) 
{

    hrtimer_cancel(&my_hr_timer);   

    pr_info(MODULE_LOG_NAME "Goodbye, Kernel\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example hr_timer lkm");
MODULE_VERSION("0.01");

module_init(hr_timer_init);
module_exit(hr_timer_exit);