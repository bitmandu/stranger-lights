# Makefile

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -g -Wall -Wpedantic -Os -DF_CPU=8000000UL -DBAUD=9600UL
LDFLAGS = -Wl,-Map,$(TARGET).map
LIBS =

MCU = atmega328p
PROGRAMMER = usbasp

all: stranger-lights.elf
stranger-lights.elf: ledstrip.o usart.o stranger-lights.o

ledstrip.o: rgb.h ws2811.h pinout.h ledstrip.h
usart.o: usart.h
stranger-lights.o: rgb.h ledstrip.h pinout.h usart.h

%.elf: %.o
	$(CC) $(LDFLAGS) -mmcu=$(MCU) -o $@ $^ $(LIBS)

%.o: %.c
	 $(CC) $(CFLAGS) -mmcu=$(MCU) -c -o $@ $<

%.hex: %.elf
	 $(OBJCOPY) -j .text -j .data -O ihex $< $@

flash: stranger-lights.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$<

clean:
	rm -f *.elf *.hex *.map *.o
