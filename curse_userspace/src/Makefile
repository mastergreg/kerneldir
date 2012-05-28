TARGET = libcurse.so
CC = gcc
LD = ld
OPT = 2
INCLUDEDIR = ../include


LDFLAGS += 

CCFLAGS += -I$(INCLUDEDIR)
CCFLAGS += -O$(OPT) -Werror -Wextra -Wall -fPIC

CCFILES += $(wildcard *.c)
OBJ +=  $(patsubst %.c,%.o,$(CCFILES))


all: $(TARGET)

%.o:	%.c
	$(CC) -c $(CCFLAGS) $< -o $@

lib%.so:	%.o
	$(LD) -G $(LDFLAGS) $< -o $@


.PHONY:	clean all indent
clean:
	rm -f $(OBJ) $(TARGET)
indent:
	astyle --style=linux $(CCFILES)
