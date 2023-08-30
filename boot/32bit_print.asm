[bits 32]

VIDEO_MEMORY EQU 0xb8000
WHITE equ 0x0f

; ebx contains pointer to the first char of the string
print_str:
    pusha
    mov edx, VIDEO_MEMORY

print_str_loop:
    mov al, [ebx]
    mov ah, WHITE

    cmp al, 0
    je print_str_end

    mov [edx], ax
    add edx, 2
    add ebx, 1
    jmp print_str_loop

print_str_end:
    popa
    ret
