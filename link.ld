ENTRY(_entry)
SECTIONS {
    . = 0x0;
    _start = .;
    .text : {
        KEEP( *(.text.top) )
        *(.text)
    }
    . = ALIGN(4096);

    .data : {
        *(.data)
    }
    . = ALIGN(4096);

    .rodata : {
        *(.rodata)
    }
    . = ALIGN(4096);

    .bss : {
        *(.bss)
    }
    . = ALIGN(4096);

    _end = .;
}