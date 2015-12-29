# http://sourceforge.net/projects/stm32flash/
STM32FLASHDIR ?= $(HOME)/BUILD/stm32flash/
# https://github.com/texane/stlink
STUTILDIR ?= $(HOME)/BUILD/stlink/
# http://openocd.org/
OPENOCDDIR ?= $(HOME)/BUILD/openocd/
OPENOCDCMD ?= $(OPENOCDDIR)/src/openocd -f $(OPENOCDDIR)/tcl/interface/stlink-v2.cfg -f $(OPENOCDDIR)/tcl/target/stm32f0x.cfg -s $(OPENOCDDIR)/tcl/
# https://github.com/libopencm3/libopencm3
LIBOPENCM3DIR ?= ../SHARED/libopencm3/

TTYDEV ?= /dev/ttyUSB0
SOC ?= STM32F0

PREFIX ?= arm-none-eabi
CFLAGS  = -std=c99 -Wall -O2 -g
CFLAGS += -mcpu=cortex-m0 -mthumb
CFLAGS += -nostartfiles -ffreestanding

CFLAGS += -I$(LIBOPENCM3DIR)/include
CFLAGS += -L$(LIBOPENCM3DIR)/lib
CFLAGS += -L$(LIBOPENCM3DIR)/../
CFLAGS += -D$(SOC)

LDFLAGS += -lopencm3_stm32f0

.PHONY: all flash flashuart flashstlink lib

all: main.elf
flash: flashstlink

lib:
	make -C $(LIBOPENCM3DIR)

main.elf: main.c $(SRCS) | lib
	$(PREFIX)-gcc $(CFLAGS) -o $@ -T stm32f030x6.ld $^ $(LDFLAGS)

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
