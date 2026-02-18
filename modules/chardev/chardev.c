// modules/chardev/chardev.c
// Character Device Driver LKM
// Creates /dev/chardev — supports open, read, write, release

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple Character Device LKM");

#define DEVICE_NAME "chardev"
#define BUF_SIZE    256

static int    major_number;
static char   message[BUF_SIZE] = {0};
static int    message_len = 0;

// --- File Operations ---

static int dev_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "[chardev] Device opened\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char __user *buffer,
                        size_t len, loff_t *offset)
{
    int err = copy_to_user(buffer, message, message_len);
    if (err) {
        printk(KERN_ERR "[chardev] Failed to send data to user\n");
        return -EFAULT;
    }
    printk(KERN_INFO "[chardev] Sent %d bytes to user\n", message_len);
    return message_len;
}

static ssize_t dev_write(struct file *filep, const char __user *buffer,
                         size_t len, loff_t *offset)
{
    if (len > BUF_SIZE - 1) len = BUF_SIZE - 1;
    if (copy_from_user(message, buffer, len)) return -EFAULT;
    message[len] = '\0';
    message_len = len;
    printk(KERN_INFO "[chardev] Received %zu bytes from user\n", len);
    return len;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "[chardev] Device closed\n");
    return 0;
}

static struct file_operations fops = {
    .open    = dev_open,
    .read    = dev_read,
    .write   = dev_write,
    .release = dev_release,
};

// --- Init / Exit ---

static int __init chardev_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "[chardev] Failed to register major number\n");
        return major_number;
    }
    printk(KERN_INFO "[chardev] Registered with major number %d\n", major_number);
    printk(KERN_INFO "[chardev] Run: sudo mknod /dev/%s c %d 0\n",
           DEVICE_NAME, major_number);
    return 0;
}

static void __exit chardev_exit(void)
{
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "[chardev] Module unloaded\n");
}

module_init(chardev_init);
module_exit(chardev_exit);
