TARGET = curse.so
CC = gcc-4.4
CCFLAGS +=
OPT = 2

CCFLAGS += -g -O0 -Werror -Wall -Wextra -Wuninitialized -fPIC



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
