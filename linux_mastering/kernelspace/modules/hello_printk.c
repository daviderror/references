#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert W. Oliver II");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

static int __init hello_init( void ) { 
   printk(KERN_INFO "Hello, kernel!\n");
   return 0; 
} 

static void __exit hello_exit( void ) { 
   printk(KERN_INFO "Goodbye, kernel!\n");
} 

module_init( hello_init ); 
module_exit( hello_exit );