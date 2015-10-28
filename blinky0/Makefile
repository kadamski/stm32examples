# http://sourceforge.net/projects/stm32flash/
STM32FLASHDIR ?= $(HOME)/BUILD/stm32flash/
# https://github.com/texane/stlink
STUTILDIR ?= $(HOME)/BUILD/stlink/
# http://openocd.org/
OPENOCDDIR ?= $(HOME)/BUILD/openocd/
OPENOCDCMD ?= $(OPENOCDDIR)/src/openocd -f $(OPENOCDDIR)/tcl/interface/stlink-v2.cfg -f $(OPENOCDDIR)/tcl/target/stm32f0x.cfg -s $(OPENOCDDIR)/tcl/

TTYDEV ?= /dev/ttyUSB0

PREFIX ?= arm-none-eabi
CFLAGS  = -std=c99 -Wall -O2 -g
CFLAGS += -mcpu=cortex-m0 -mthumb
CFLAGS += -nostdlib -nostartfiles -ffreestanding

.PHONY: all flash flashuart flashstlink

all: main.elf
flash: flashstlink

main.elf: main.c stm32f030x6_startup.s
	$(PREFIX)-gcc $(CFLAGS) -o $@ -T stm32f030x6.ld $^

main.bin: main.elf
	$(PREFIX)-objcopy $< $@ -O binary

main.list: main.elf
	$(PREFIX)-objdump -D $< > main.list

flashuart: main.bin
	$(STM32FLASHDIR)/stm32flash -w $< -g 0x00 $(TTYDEV)

flashstlink: main.bin
	$(STUTILDIR)/st-flash write $< 0x8000000

flashocd: main.bin
	$(OPENOCDCMD) -c init -c "reset init" -c "flash write_image erase main.bin 0x8000000" -c "reset run" -c "shutdown"

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
