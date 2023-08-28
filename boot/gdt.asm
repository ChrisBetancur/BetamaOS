
gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff ; limit for code segment
    dw 0x0 ; base (bits 0 - 15)
    db 0x0 ; base (bits 16 - 23)
    db 10011010b ; flags 8
    db 11001111b ; flags (4 bits) + limit
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; define the size of the gdt

    dd gdt_start ; define the start address of the GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
