TARGET = curse.so
CC = gcc
CCFLAGS +=
OPT = 2

CCFLAGS += -g -O0 -Werror -Wall -Wextra -Wuninitialized

CCFILES += $(wildcard *.c)
OBJFILES +=  $(patsubst %.c,%.o,$(CCFILES))
DEPENDS += $(wildcard *.h) 


all: $(TARGET)

%.o:	%.c
	$(CC) -c $(CCFLAGS) $<

%.so:	%.o
	ld -G $< -o $@

.PHONY:	clean all indent
clean:
	rm -f $(OBJFILES) $(TARGET)
indent:
	astyle --style=linux $(CCFILES)
