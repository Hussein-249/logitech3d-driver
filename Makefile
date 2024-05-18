CC := gcc
CFLAGS = -Wall -g
INCLUDES = -Iheader
# LIBS = -lncurses

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

# Target: JoystickModule
JoystickModule: main.o joystick.o
	$(CC) $(OPTIONS) $(INCLUDES) -o JoystickModule main.o joystick.o

main.o: src/main.c headers/joystick.h
	$(CC) $(OPTIONS) $(INCLUDES) -c src/main.c

joystick.o: src/joystick.c headers/joystick.h
	$(CC) $(OPTIONS) $(INCLUDES) -c src/joystick.c

clean:
	rm -f *.o JoystickModule


standalone:
