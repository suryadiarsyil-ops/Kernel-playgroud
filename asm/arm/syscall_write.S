// asm/arm/syscall_write.S
// ARM64 (AArch64) Assembly — Direct syscall: write to stdout
// Build: aarch64-linux-gnu-as syscall_write.S -o syscall_write.o
//        aarch64-linux-gnu-ld syscall_write.o -o syscall_write

.section .data
msg:    .ascii "Hello from ARM64 ASM!\n"
msg_len = . - msg

.section .text
.global _start
_start:
    // sys_write(fd=1, buf=msg, count=msg_len)
    mov     x8, #64         // syscall: write
    mov     x0, #1          // fd: stdout
    adr     x1, msg         // buf
    mov     x2, #msg_len    // count
    svc     #0

    // sys_exit(code=0)
    mov     x8, #93         // syscall: exit
    mov     x0, #0          // exit code
    svc     #0
