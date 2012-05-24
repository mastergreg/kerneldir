
CC=gcc-4.4
CCFLAGS=-I../linux/include/

SRCFILES=$(wildcard *.c)
OBJFILES=$(patsubst %.c,%.o,$(SRCFILES))
TARGET=curse_tester.out
all:	$(TARGET)

$(TARGET):	$(OBJFILES)
	$(CC)	$(CCFLAGS) $^ -o $(TARGET)


*.o:	*.c
	$(CC) $(CCFLAGS) $< -c

clean:
	$(RM) $(OBJFILES) $(TARGET)
