#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

// Module metadata
MODULE_AUTHOR("mbrav");
MODULE_DESCRIPTION("Gigachad Kernel Module");
MODULE_LICENSE("GNU");

// Custom init and exit methods
static int __init custom_init(void) {
  printk(KERN_INFO "Gigachad Kernel Module loaded!\n");
  return 0;
}

static void __exit custom_exit(void) {
  printk(KERN_INFO "Gigachad Kernel Module unloaded!\n");
}

module_init(custom_init);
module_exit(custom_exit);
