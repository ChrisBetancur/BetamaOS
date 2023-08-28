[org 0x7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

call load_kernel

jmp $

BOOT_DRIVE db 0

%include "boot/disk.asm"

[bits 16]

load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 32 ; FIND A WHY TO CALCULATE HOW MUCH SPACE SHOULD YOU RESERVE FOR THE KERNEL

    mov dl, [BOOT_DRIVE]
    call disk_load
    ret


[bits 32]

begin_pm:
    call KERNEL_OFFSET
    jmp $

times 510 - ($-$$) db 0
dw 0xaa55
