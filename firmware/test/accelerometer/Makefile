PRG            = accelerometer
OBJ            = accelerometer.o
PROGRAMMER     = usbtiny
MCU_TARGET     = atmega48
AVRDUDE_TARGET = atmega48
OPTIMIZE       = -Os 
DEFS           =
LIBS           =
INCLUDES       = ../../include
HZ             = 32768
CC             = avr-gcc
LFUSE          = 0xC4
HFUSE          = 0xFF
EFUSE          = 0xFF
 
override CFLAGS        = -g -I$(INCLUDES) -DF_CPU=$(HZ) -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,-Map,$(PRG).map
 
OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump
 
all: $(PRG).elf lst text #eeprom
 
$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
 
clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak *.hex *.bin *.srec
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)
 
lst:  $(PRG).lst
 
%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@
 
# Rules for building the .text rom images
 
text: hex bin srec
 
hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec
 
%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
 
%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@
 
%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@
 
# Rules for building the .eeprom rom images
 
eeprom: ehex ebin esrec
 
 
ehex:  $(PRG)_eeprom.hex
#ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec
 
%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@
 
#%_eeprom.srec: %.elf
#	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@
 
%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@
 
 
# command to program chip (invoked by running "make install")
install:  $(PRG).hex
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 160 -v \
         -U flash:w:$(PRG).hex 
 
fuse:
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 160 -v \
	-U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m

ddd: gdbinit
	ddd --debugger "avr-gdb -x $(GDBINITFILE)"
 
gdbserver: gdbinit
	simulavr --device $(MCU_TARGET) --gdbserver
 
gdbinit: $(GDBINITFILE)
 
$(GDBINITFILE): $(PRG).hex
	@echo "file $(PRG).elf" > $(GDBINITFILE)
 
	@echo "target remote localhost:1212" >> $(GDBINITFILE)
	@echo "load"                         >> $(GDBINITFILE)
	@echo "break main"                   >> $(GDBINITFILE)
	@echo
	@echo "Use 'avr-gdb -x $(GDBINITFILE)'"
