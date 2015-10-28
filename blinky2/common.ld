SECTIONS
{
    .vectors :
    {
        . = ALIGN(4);
        *(.isr_vector)
        . = ALIGN(4);
    } > flash

    .text :
    {
        . = ALIGN(4);
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > flash

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = . ;
        _sbss = __bss_start__ ;
        *(.bss*)
        *(COMMON)
        __bss_end__ = . ;
        _ebss = __bss_end__ ;
        . = ALIGN(4);
    } > sram

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata*)
        . = ALIGN(4);
    } > flash

    _sidata = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = . ;
        *(.data*)
        . = ALIGN(4);
        _edata = . ;
    } > sram AT> flash
}

_estack = ORIGIN(sram) + LENGTH(sram);
