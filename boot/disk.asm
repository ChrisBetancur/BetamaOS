
; dh indicates how many sectors to read param
disk_load:
    pusha

    push dx

    ; set params for disk read function from BIOS
    mov ah, 0x02 ; perform real instruction
    mov al, dh ; num of sectors to read
    mov cl, 0x02 ; IDK
    mov ch, 0x0
    mov dh, 0x00

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error
    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah ; ah = error code, dl = disk drive that dropped the error
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0
