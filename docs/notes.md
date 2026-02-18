# LKM + Assembly — Notes & Cheatsheet

## Inline Assembly Syntax (GCC)

```c
__asm__ volatile (
    "assembly instructions"
    : output operands
    : input operands
    : clobbered registers
);
```

### Common Constraints
| Constraint | Meaning             |
|------------|---------------------|
| `"r"`      | General register    |
| `"m"`      | Memory operand      |
| `"i"`      | Immediate integer   |
| `"=r"`     | Output to register  |

---

## x86-64 Kernel Registers of Interest

| Register | Purpose                         |
|----------|---------------------------------|
| CR0      | System control (Protected Mode) |
| CR3      | Page table base address         |
| CR4      | Extended features               |
| RFLAGS   | CPU flags                       |

---

## ARM64 System Registers (MRS/MSR)

| Register    | Purpose                      |
|-------------|------------------------------|
| MIDR_EL1    | CPU identification           |
| MPIDR_EL1   | Multiprocessor affinity      |
| SCTLR_EL1   | System control               |
| DAIF        | Interrupt mask flags         |

```asm
mrs x0, midr_el1     // read
msr sctlr_el1, x0    // write
```

---

## Kernel Logging Levels

```c
printk(KERN_EMERG   "...");  // 0 — system unusable
printk(KERN_ALERT   "...");  // 1 — action must be taken
printk(KERN_CRIT    "...");  // 2 — critical condition
printk(KERN_ERR     "...");  // 3 — error
printk(KERN_WARNING "...");  // 4 — warning
printk(KERN_NOTICE  "...");  // 5 — normal but significant
printk(KERN_INFO    "...");  // 6 — informational
printk(KERN_DEBUG   "...");  // 7 — debug
```

---

## Safety Checklist

- [ ] Test in VM (QEMU/VirtualBox/VMware)
- [ ] Always `rmmod` before rebooting
- [ ] Check `dmesg` after `insmod`
- [ ] Never dereference null pointers — no recovery in kernel space
- [ ] Use `MODULE_LICENSE("GPL")` to avoid tainting the kernel
