#mohamed sultan

cc=arm-none-eabi-
CFLAGS= -mcpu=cortex-m4 -gdwarf-2 -g
INCS=-I .
LIBS=     #IF I HAVE LIBRARY
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
AsOBJ=$(AS:.s=.o)
project_name=output_cortex_m4
all:$(project_name).bin
	@echo "done..............."

%.o:%.s

	$(cc)as.exe $(CFLAGS) $< -o $@
%.o:%.c
	$(cc)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@


$(project_name).elf:$(OBJ) $(AsOBJ)
	$(cc)ld.exe -T linker_script.ld $(OBJ) $(AsOBJ) $(LIBS) -o $@ -Map=Map_file.map
	cp $(project_name).elf $(project_name).axf

$(project_name).bin:$(project_name).elf
	$(cc)objcopy.exe $<   $@

clean_all:
	rm *.o *.elf *.bin
clean:
	rm  *.elf *.bin
