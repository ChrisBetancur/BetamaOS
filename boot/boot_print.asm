
; bx contains the pointer to the base of the message
print:
    pusha

start:
    mov al, [bx]
    cmp al, 0
    je done

    mov ah, 0x0a
    int 0x10

    add bx, 1
    jmp start

done:
    popa
    ret

print_nl:
    pusha
    mov al, 0x0e
    mov ah, 0x0a
    int 0x10

    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret

