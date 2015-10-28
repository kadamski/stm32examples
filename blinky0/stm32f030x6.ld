MEMORY
{
    sram : ORIGIN = 0x20000000, LENGTH = 4K
    flash : ORIGIN = 0x08000000, LENGTH = 16K
}

SECTIONS
{
    .vectors : { *(.vectors*) } > flash
    .text : { *(.text*) } > flash
}
