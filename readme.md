# Video to Text 'Kernel'

Videos can now run on plain i386 hardware. I'm not sure either OS or kernel fit the name, but oh well.
It's kind of an operating system, where you have a bootloader (in this case GRUB) and loads the kernel into memory and executes it.
Idk what else to put here, I'm really bad with READMEs. :/

Requirements:
* NASM
* i686-elf toolchain
* GRUB utils

You can build it by running

`make kernel`

and it will make the `playback.elf` file.

In order to make it runnable on real hardware (or just build the ISO), you can run

`make iso`

after the last command and it will make the `playback.iso` file.

Now you're ready to flash the ISO!
