// modules/hello/hello.c
// Basic Linux Kernel Module — Hello World
// Demonstrates: module_init, module_exit, printk

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Hello World LKM");
MODULE_VERSION("1.0");

static int __init hello_init(void)
{
    printk(KERN_INFO "[hello] Module loaded — Hello, Kernel!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "[hello] Module unloaded — Goodbye, Kernel!\n");
}

module_init(hello_init);
module_exit(hello_exit);
