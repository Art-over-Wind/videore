ENTRY(_entry)
SECTIONS {
    . = 0x0;
    _start = .;
    .text : {
        KEEP( *(.text.top) )
        *(.text)
    }
    . = ALIGN(4096);

    PROVIDE(__init_array_start = .);
    .init.array : {
        *(.init_array)
        *(.init_array.*)
        *(.ctors)
        *(.ctors.*)
    }
    PROVIDE(__init_array_end = .);
    . = ALIGN(4096);

    .data : {
        *(.data)
    }
    . = ALIGN(4096);

    .rodata : {
        *(.rodata)
    }
    . = ALIGN(4096);

    _bss_start = .;
    .bss : {
        *(.bss)
    }
    . = ALIGN(4096);
    _bss_end = .;
    _bss_size = (_bss_end - _bss_start) >> 3;

    _end = .;

    _usable = 0x80000000;
}