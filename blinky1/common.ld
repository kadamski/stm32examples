SECTIONS
{
    .vectors : { *(.vectors*) } > flash
    .text : { *(.text*) } > flash
}
