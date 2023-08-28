
disk_load:
    pusha

    push dx

    ; set params for disk read function from BIOS

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x0
    mov dh, 0x00

    ; call disk read
    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error

    popa
    ret


%include "boot/boot_print.asm"

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR:
    db "[BOOT] Disk read error", 0

SECTORS_ERROR:
    db "[BOOT] Incorrect number of sectors read", 0
