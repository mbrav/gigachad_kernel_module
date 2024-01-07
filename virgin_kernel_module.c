/*
 * virgin_kernel_module.c - The simplest minimal kernel module.
 */

// Include Linux Kernel libs
#include <linux/init.h> /* Needed for the macros */
#include <linux/module.h>  /* Needed by all modules */

// Module metadata
MODULE_AUTHOR("mbrav");
MODULE_DESCRIPTION("Virgin Kernel Module");
MODULE_LICENSE("GPL-2.0+");

// Custom init method
static int __init custom_init(void) {
    printk(KERN_INFO "Virgin Kernel Module loaded!\n");
    return 0;
}

// Custom exit method
static void __exit custom_exit(void) {
    printk(KERN_INFO "Virigin Kernel Module unloaded!\n");
}

// Load modules
module_init(custom_init);
module_exit(custom_exit);

