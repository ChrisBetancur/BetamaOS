[bits 16]
switch_to_pm:
    cli ; Turns off interrupts

    lgdt [gdt_descriptor] ; loads the gdt table which defins the protected mode segments for code and data

    mov eax, cr0 ; indirectly sets the first bit of the cpu control register to 1 allowing the switch to 32 bit
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm ; a far jump is issued to flush the pipeline (completes all instrucitons currently in different stages in the pipeline)

[bits 32]

init_pm:
    ; make all the segment registers point to the segment defined in the GDT
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

;update stack position so it is right at the top of the free space
    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM ; exit and call well know label
