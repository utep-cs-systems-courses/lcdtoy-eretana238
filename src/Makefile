# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: play.elf

#additional rules for files
play.elf: ${COMMON_OBJECTS} main.o wdt_handler.o buzzer.o soundEngine.o spaceship.o switches.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lShape -lCircle -lp2sw

load: play.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.o: buzzer.h buzzer.c

soundEngine.o: buzzer.h soundEngine.h soundEngine.c

switches.o: spaceship.h switches.h switches.c

spaceship.o: spaceship.h spaceship.c
