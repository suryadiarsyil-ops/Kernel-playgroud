; asm/x86/syscall_write.asm
; x86-64 Assembly — Direct syscall: write "Hello from ASM\n" to stdout
; Build:  nasm -f elf64 syscall_write.asm -o syscall_write.o
;         ld syscall_write.o -o syscall_write
; Run:    ./syscall_write

section .data
    msg     db  "Hello from x86-64 ASM!", 10   ; message + newline
    msg_len equ $ - msg

section .text
    global _start

_start:
    ; sys_write(fd=1, buf=msg, count=msg_len)
    mov     rax, 1          ; syscall number: write
    mov     rdi, 1          ; fd: stdout
    mov     rsi, msg        ; buffer
    mov     rdx, msg_len    ; count
    syscall

    ; sys_exit(code=0)
    mov     rax, 60         ; syscall number: exit
    xor     rdi, rdi        ; exit code 0
    syscall
