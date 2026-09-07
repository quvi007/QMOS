ENTRY(boot)

SECTIONS {
    . = 0x80200000;

    .text :{ /* program source code */
        KEEP(*(.text.boot));
        *(.text .text.*);
    }

    .rodata : ALIGN(4) { /* read-only data */
        *(.rodata .rodata.*);
    }

    .data : ALIGN(4) { /* initialized data for read-write */
        *(.data .data.*);
    }

    .bss : ALIGN(4) { /* zeroed globals */
        __bss = .; /* have to keep track of where bss starts */
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .; /* also keep track of where bss ends */
    }

    . = ALIGN(4);
    . += 128 * 1024; /* reserve 128 KB for stack */
    __stack_top = .; /* point to the stack_top */
}