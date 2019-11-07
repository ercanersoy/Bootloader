#############
# Variables #
#############

# Device type (GCC)
DEVICE = atmega328p

# Clock frequency in Hz
F_CPU = 16000000

# Programmer software
PROGRAMMER_SOFTWARE = avrdude

# Programmer software parameters
PROGRAMMER_SOFTWARE_PARAMETERS = -c usbtiny -p m328p -F

# Extended fuse byte of microcontroller
EXTENDED_FUSE = efuse:w:0xff:m

# High fuse byte of microcontroller
HIGH_FUSE = hfuse:w:0xd8:m

# Low fuse byte of microcontroller
LOW_FUSE = lfuse:w:0xff:m

# Start bootloader section
START_BOOTLOADER_SECTION = 0x7000

# Linker
LD = avr-gcc

# Compiler
CC = avr-gcc

# Objcopy
OBJCOPY = avr-objcopy

# Linker flags
LDFLAGS = -O1 -DF_CPU=$(F_CPU) -mmcu=$(DEVICE) -Ttext=$(START_BOOTLOADER_SECTION)

# Compiler flags
CFLAGS = -O1 -c -DF_CPU=$(F_CPU) -mmcu=$(DEVICE) -Ttext=$(START_BOOTLOADER_SECTION)

# Object Files
OBJECTS = main.o standard_library/standard_library.o platforms/megaavr/http_user_interface.o platforms/megaavr/uart.o platforms/megaavr/wiznet_5100.o

###################
# Building Events #
###################

# Last event
all: binaries/bootloader.hex binaries/bootloader.bin

# Create bootloader.bin
binaries/bootloader.bin: binaries/bootloader.elf
	$(OBJCOPY) -j .text -j .data -O binary $? $@

# Create bootloader.hex
binaries/bootloader.hex: binaries/bootloader.elf
	$(OBJCOPY) -j .text -j .data -O ihex $? $@

# Create bootloader.elf
binaries/bootloader.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $? -o $@

# Create main object
main.o: main.c
	$(CC) $(CFLAGS) $? -o $@

# Create standard library object
standard_library/standard_library.o: standard_library/standard_library.c
	$(CC) $(CFLAGS) $? -o $@

# Create http object
platforms/megaavr/http_user_interface.o: platforms/megaavr/http_user_interface.c
	$(CC) $(CFLAGS) $? -o $@

# Create uart object
platforms/megaavr/uart.o: platforms/megaavr/uart.c
	$(CC) $(CFLAGS) $? -o $@

# Create wiznet_5100 object
platforms/megaavr/wiznet_5100.o: platforms/megaavr/wiznet_5100.c
	$(CC) $(CFLAGS) $? -o $@

####################
# Installing Event #
####################

install: binaries/bootloader.hex
	$(PROGRAMMER_SOFTWARE) $(PROGRAMMER_SOFTWARE_PARAMETERS) -U flash:w:binaries/bootloader.hex:i

################
# Setting Fuse #
################

set-fuses:
	$(PROGRAMMER_SOFTWARE) $(PROGRAMMER_SOFTWARE_PARAMETERS) -U $(EXTENDED_FUSE)
	$(PROGRAMMER_SOFTWARE) $(PROGRAMMER_SOFTWARE_PARAMETERS) -U $(HIGH_FUSE)
	$(PROGRAMMER_SOFTWARE) $(PROGRAMMER_SOFTWARE_PARAMETERS) -U $(LOW_FUSE)

###################
# Cleaning Events #
###################

# Clean all compiled and linked files
clean:
	rm -f binaries/*.* $(OBJECTS)

# Clean all compiled files
clean-objects:
	rm -f $(OBJECTS)
