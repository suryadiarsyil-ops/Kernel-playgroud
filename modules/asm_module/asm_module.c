// modules/asm_module/asm_module.c
// LKM with Inline Assembly — x86-64 & ARM examples
// Demonstrates: reading CPU registers, inline asm in kernel space

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Inline Assembly inside LKM");

// ============================================================
// x86-64: Read CR0 control register
// CR0 bit 0 = Protected Mode Enable (PE)
// ============================================================
#if defined(__x86_64__)

static void read_cr0_asm(void)
{
    unsigned long cr0_val;
    __asm__ volatile (
        "mov %%cr0, %0"
        : "=r" (cr0_val)
    );
    printk(KERN_INFO "[asm_module] x86-64 CR0 = 0x%lx\n", cr0_val);
    printk(KERN_INFO "[asm_module] Protected Mode: %s\n",
           (cr0_val & 1) ? "ENABLED" : "DISABLED");
}

static void cpuid_vendor(void)
{
    unsigned int eax, ebx, ecx, edx;
    char vendor[13] = {0};

    __asm__ volatile (
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(0)
    );
    *(unsigned int *)(vendor)     = ebx;
    *(unsigned int *)(vendor + 4) = edx;
    *(unsigned int *)(vendor + 8) = ecx;
    printk(KERN_INFO "[asm_module] CPU Vendor: %s\n", vendor);
}

// ============================================================
// ARM64: Read MIDR_EL1 (Main ID Register)
// ============================================================
#elif defined(__aarch64__)

static void read_midr_asm(void)
{
    unsigned long midr;
    __asm__ volatile (
        "mrs %0, midr_el1"
        : "=r" (midr)
    );
    printk(KERN_INFO "[asm_module] ARM64 MIDR_EL1 = 0x%lx\n", midr);
}

#else
    #warning "Unsupported architecture — asm_module will run without asm demos"
#endif


// --- Init / Exit ---

static int __init asm_module_init(void)
{
    printk(KERN_INFO "[asm_module] Loaded\n");

#if defined(__x86_64__)
    read_cr0_asm();
    cpuid_vendor();
#elif defined(__aarch64__)
    read_midr_asm();
#else
    printk(KERN_INFO "[asm_module] No asm demo for this arch\n");
#endif

    return 0;
}

static void __exit asm_module_exit(void)
{
    printk(KERN_INFO "[asm_module] Unloaded\n");
}

module_init(asm_module_init);
module_exit(asm_module_exit);
