CFLAGS += -Wall -I../include -I ./include -L../lib -os
KERN_CFLAGS = -c -m32 -nostdlib -nostdinc -nostartfiles -Wall -I.

all: playback.exe

data.h:
	python3 convert.py
	xxd -i data > data.h

playback: playback.c data.h
	gcc $(CFLAGS) -o playback playback.c

playback.exe: playback.c data.h
	i686-w64-mingw32-gcc $(CFLAGS) -o playback.exe playback.c

kernel: KERN_playback.c data.h
	nasm -felf32 -o boot.o boot.asm
	nasm -felf32 -o code.o code.asm
	i686-elf-gcc $(KERN_CFLAGS) -o common.o common.c
	i686-elf-gcc $(KERN_CFLAGS) -o descriptor_tables.o descriptor_tables.c
	i686-elf-gcc $(KERN_CFLAGS) -o isr.o isr.c
	i686-elf-gcc $(KERN_CFLAGS) -o string.o string.c
	i686-elf-gcc $(KERN_CFLAGS) -o assembly.o assembly.c
	i686-elf-gcc $(KERN_CFLAGS) -o screen.o screen.c
	i686-elf-gcc $(KERN_CFLAGS) -o playback.o KERN_playback.c
	i686-elf-ld -T linker.ld -m elf_i386 -o playback.elf boot.o code.o common.o descriptor_tables.o isr.o string.o assembly.o screen.o playback.o

iso: kernel
	cp playback.elf iso
	grub-mkrescue -o playback.iso ./iso

# I personally think that using -f is a bad idea
# but whatever

clean:
	rm -f data
	rm -f data.h
	rm -f playback
	rm -f playback.exe
	rm -f *.o
