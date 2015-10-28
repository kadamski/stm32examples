.cpu cortex-m0
.thumb

.section .vectors, "a"
/* RM0360 - 11.1.3, p 171 */
.word   0x20001000  /* stack top address */
.word   _start      /* 0x04 Reset */
.word   hang        /* 0x08 NMI */
.word   hang        /* 0x0C HardFault */
.word   hang        /* 0x10 EMPTY */
.word   hang        /* 0x14 EMPTY */
.word   hang        /* 0x18 EMPTY */
.word   hang        /* 0x1C EMPTY */
.word   hang        /* 0x20 EMPTY */
.word   hang        /* 0x24 EMPTY */
.word   hang        /* 0x28 EMPTY */
.word   hang        /* 0x2C SVCall */
.word   hang        /* ... */

.section .text
.thumb_func
.global _start
_start:
    bl _main
    b hang

.thumb_func
hang:   b .

.end
