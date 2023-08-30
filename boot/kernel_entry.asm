[bits 32]
[extern main] ; defines the calling point to kernel.c such that main is the name of the function that should be starting at
    call main
    jmp $
