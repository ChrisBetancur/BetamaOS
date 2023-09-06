[org 0x7c00]

KERNEL_OFFSET equ 0x1000 ; memory offset to which the kernel will be loaded

    mov [BOOT_DRIVE], dl ; BIOS stores the boot drive in dl

    ; setting up stack
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel
    call switch_to_pm

    jmp $

%include "boot/boot_sect_print.asm"
%include "boot/32bit_print.asm"
%include "boot/gdt.asm"
%include "boot/disk.asm"
%include "boot/switch.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    ; RESEARCH how much space should i save for the OS
    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 16 ; will load 15 sectors from the boot disk instead of 1 so that to prevent the issues when trying to detect that we didn't read enough sectors
    ; this prevents an unloaded sector boundary
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_str

    call KERNEL_OFFSET ; gives control to the kernel

    jmp $

; global vars
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode...", 0
MSG_PROT_MODE db "Started in 32-bit protected mode...", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

times 510 - ($-$$) db 0
dw 0xaa55
