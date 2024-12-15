.section .text.top
.space 0x200
.extern _main
.global _entry

_entry:
    ; Load address.
    lea r0, _entry

    bl _main

_halt:
    b _halt