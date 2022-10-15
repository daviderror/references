#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 

#define MODULE_LOG_NAME "hello_world-lkm: "

static int __init hello_init( void ) 
{ 
    pr_info(MODULE_LOG_NAME "Hello, kernel!\n");
    return 0; 
} 

static void __exit hello_exit( void ) 
{ 
    pr_info(MODULE_LOG_NAME "Goodbye, kernel!\n");
} 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sae");
MODULE_DESCRIPTION("A linux example hello_world lkm.");
MODULE_VERSION("0.01");

module_init( hello_init ); 
module_exit( hello_exit );