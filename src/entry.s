.section .text.top
.space 0x200
.extern _main
.global _entry

.ascii "Hello from ASM"

_entry:
    bl _main

_halt:
    b _halt