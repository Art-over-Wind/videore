.section .text.top
.space 0x200
.extern _main
.global _entry

_entry:
    ; Kernel stack pointer.
    ld r0, _entry
    mov sp, r0

    bl _main

_halt:
    b _halt