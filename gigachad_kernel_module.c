/*
 * gigachad_kernel_module.c - The Chad kernel module.
 * Registers a new /proc/gigachad_hello proc file
 * Registers a new /proc/gigachad_sha256 proc file that outputs a SHA256 sum
 */

// Include Linux Kernel libs
#include <linux/init.h>            /* Needed for the macros */
#include <linux/module.h>          /* Needed by all modules */
#include <linux/moduleparam.h>     /* Needed for definining module parameters */
#include <linux/proc_fs.h>         /* Needed for accesing /proc FS */
#include <linux/version.h>         /* Needed for accesing kernel version info */
#include <crypto/internal/hash.h>  /* Needed for accesing hashing shiet */

// Module metadata
MODULE_AUTHOR("mbrav <mbrav@protonmail.com>");
MODULE_DESCRIPTION("Gigachad Kernel Module");
MODULE_LICENSE("GPL");

// Define module parameters
static unsigned int chad_level = 420;
static unsigned int sha256_length = 64;
module_param(chad_level, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
module_param(sha256_length , int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(chad_level, "Specify what chad level are you");
MODULE_PARM_DESC(sha256_length, "Specify sha256 output lenght");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

// Register new /proc names
#define procfs_name_1 "gigachad_hello"
#define procfs_name_2 "gigachad_sha256"
static struct proc_dir_entry *proc_file_1;
static struct proc_dir_entry *proc_file_2;

/* HELPER FUNCTIONS*/
static void show_hash_result(char *plaintext, char *hash_sha256)
{
    int i;
    char str[sha256_length * 2 + 1];
    pr_info("%s: string in: \"%s\"\n", procfs_name_2, plaintext);
    for (i = 0; i < sha256_length; i++)
        sprintf(&str[i * 2], "%02x", (unsigned char)hash_sha256[i]);
    str[i * 2] = 0;
    pr_info("%s: %s\n", procfs_name_2, str);
}

/* Hello Gigachad procfile function */
static ssize_t procfile_read_1(
        struct file *file_pointer, 
        char __user *buffer,
        size_t buffer_length, loff_t *offset)
{
    char s[23] = "Hello GigaChad module!\n";
    int len = sizeof(s);
    ssize_t ret = len;
    if (*offset >= len || copy_to_user(buffer, s, len)) {
        pr_info("%s: copy_to_user failed\n", procfs_name_1);
        ret = 0;
    } else {
        pr_info("%s: procfile read %s\n", procfs_name_1, file_pointer->f_path.dentry->d_name.name);
        *offset += len;
    }
    return ret;
}

/* SHA256 Gigachad procfile function */
static ssize_t procfile_read_2(
        struct file *file_pointer, 
        char __user *buffer,
        size_t buffer_length, loff_t *offset)
{
    char *plaintext = "This is a test";
    char hash_sha256[sha256_length ];
    struct crypto_shash *sha256;
    struct shash_desc *shash;
    sha256 = crypto_alloc_shash("sha256", 0, 0);
    if (IS_ERR(sha256)) {
        pr_err(
            "%s - %s(): Failed to allocate sha256 algorithm, enable CONFIG_CRYPTO_SHA256 and try again.\n",
                procfs_name_2,
                __func__);
        return -1;
    }
    shash = kmalloc(sizeof(struct shash_desc) + crypto_shash_descsize(sha256),
            GFP_KERNEL);
    if (!shash)
        return -ENOMEM;
    shash->tfm = sha256;
    if (crypto_shash_init(shash))
        return -1;
    if (crypto_shash_update(shash, plaintext, strlen(plaintext)))
        return -1;
    if (crypto_shash_final(shash, hash_sha256))
        return -1;

    kfree(shash);
    crypto_free_shash(sha256);

    show_hash_result(plaintext, hash_sha256);

    int len = sizeof(hash_sha256);
    ssize_t ret = len;
    if (*offset >= len || copy_to_user(buffer, hash_sha256, len)) {
        pr_info("%s: copy_to_user failed\n", procfs_name_2);
        ret = 0;
    } else {
        pr_info("%s: procfile read %s\n", procfs_name_2, file_pointer->f_path.dentry->d_name.name);
        *offset += len;
    }
    return ret;
//    return 0;
}

#ifdef HAVE_PROC_OPS
static const struct proc_ops proc_file_fops_1 = {
    .proc_read = procfile_read_1,
};
static const struct proc_ops proc_file_fops_2 = {
    .proc_read = procfile_read_2,
};
#else
static const struct file_operations proc_file_fops_1 = {
    .read = procfile_read_1,
};
static const struct file_operations proc_file_fops_2 = {
    .read = procfile_read_2,
};
#endif

// Custom init method
static int __init custom_init(void) {
    proc_file_1 = proc_create(procfs_name_1, 0644, NULL, &proc_file_fops_1);
    proc_file_2 = proc_create(procfs_name_2, 0644, NULL, &proc_file_fops_2);
    if (NULL == proc_file_1) {
        proc_remove(proc_file_1);
        pr_alert("Error:Could not initialize /proc/%s\n", procfs_name_1);
        return -ENOMEM;
    }
    if (NULL == proc_file_2) {
        proc_remove(proc_file_2);
        pr_alert("Error:Could not initialize /proc/%s\n", procfs_name_2);
        return -ENOMEM;
    }
    pr_info("B============================o\n");
    pr_info("Gigachad Kernel Module loaded!\n");
    pr_info("chad_level:    %d\n", chad_level);
    pr_info("sha256_length: %d\n", sha256_length);
    pr_info("proc: /proc/%s created\n", procfs_name_1);
    pr_info("proc: /proc/%s created\n", procfs_name_2);
    return 0;
}

// Custom exit method
static void __exit custom_exit(void) {
    proc_remove(proc_file_1);
    proc_remove(proc_file_2);
    pr_info("B============================o\n");
    pr_info("Gigachad Kernel Module unloaded!\n");
    pr_info("proc: /proc/%s Removed!\n", procfs_name_1);
    pr_info("proc: /proc/%s Removed!\n", procfs_name_2);
}

// Load modules
module_init(custom_init);
module_exit(custom_exit);

