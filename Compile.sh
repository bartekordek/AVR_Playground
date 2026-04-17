avr-gcc main.c -o main.elf -mmcu=atmega32 -DF_CPU=1000000UL -Os
avr-objcopy main.elf -O ihex main.hex