/*
 * gigachad_kernel_module.c - The Chad kernel module.
 */

// Include Linux Kernel libs
#include <linux/init.h>         /* Needed for the macros */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/moduleparam.h>  /* Needed for definining module parameters */
#include <linux/uaccess.h>
#include <linux/proc_fs.h>      /* Needed for accesing /proc FS */
#include <linux/version.h>      /* Needed for accesing kernel version info */ 

// Module metadata
MODULE_AUTHOR("mbrav <mbrav@protonmail.com>");
MODULE_DESCRIPTION("Gigachad Kernel Module");
MODULE_LICENSE("GPL");

// Define module parameters
static unsigned int chad_level= 420;
module_param(chad_level, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(chad_level, "Specify what chad level are you");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

// Register new /proc name
#define procfs_name "gigachad"

static struct proc_dir_entry *our_proc_file;

// Read procfile function
static ssize_t procfile_read(
        struct file *file_pointer, 
        char __user *buffer,
        size_t buffer_length, loff_t *offset)
{
    char s[23] = "Hello GigaChad module!\n";
    int len = sizeof(s);
    ssize_t ret = len;
    if (*offset >= len || copy_to_user(buffer, s, len)) {
        pr_info("copy_to_user failed\n");
        ret = 0;
    } else {
        pr_info("procfile read %s\n", file_pointer->f_path.dentry->d_name.name);
        *offset += len;
    }
    return ret;
}

#ifdef HAVE_PROC_OPS
static const struct proc_ops proc_file_fops = {
    .proc_read = procfile_read,
};
#else
static const struct file_operations proc_file_fops = {
    .read = procfile_read,
};
#endif

struct Player {
  char name[12];
  int score;
};

void chad_structs(void) {
  struct Player player1;
  struct Player player2;

  player1.score = 1234;
  player2.score = 12;
  strcpy(player1.name, "Chad");
  strcpy(player2.name, "Bob");

  pr_debug("Player 1: %s (%d)\n", player1.name, player1.score);
  pr_debug("Player 2: %s (%d)\n", player2.name, player2.score);
}

// Custom init method
static int __init custom_init(void) {
    our_proc_file = proc_create(procfs_name, 0644, NULL, &proc_file_fops);
    if (NULL == our_proc_file) {
        proc_remove(our_proc_file);
        pr_alert("Error:Could not initialize /proc/%s\n", procfs_name);
        return -ENOMEM;
    }
    pr_info("B============================o\n");
    pr_info("Gigachad Kernel Module loaded!\n");
    pr_info("B======o--- Params ---o======3\n");
    pr_info("chad_level: %d\n", chad_level);
    pr_info("B======o--- Components ---o======3\n");
    pr_info("proc: /proc/%s created\n", procfs_name);
    pr_info("o============================3\n");
    chad_structs();
    return 0;
}

// Custom exit method
static void __exit custom_exit(void) {
    proc_remove(our_proc_file);
    pr_info("B============================o\n");
    pr_info("Gigachad Kernel Module unloaded!\n");
    pr_info("B======o--- Components ---o======3\n");
    pr_info("proc: /proc/%s Removed!\n", procfs_name);
    pr_info("o============================3\n");
}

// Load modules
module_init(custom_init);
module_exit(custom_exit);

