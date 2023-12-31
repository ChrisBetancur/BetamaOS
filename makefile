sources = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c shell/*.c)
headers = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h shell/*.h)
# RESEARCH WHY ADD THE INTERRUPT HERE
objects = $(sources:.c=.o cpu/interrupt.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic

cc = /home/c_bet/build-i686-elf/bin/i686-elf-gcc
gdb = /home/c_bet/build-i686-elf/bin/i686-elf-gdb

flags = -g

os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${objects}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${objects}
	i686-elf-ld -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	${gdb} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${headers}
	${cc} ${flags} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
