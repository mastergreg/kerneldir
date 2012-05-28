
CC=gcc
LDPATH=../lib

CFLAGS += -I../include/
LDFLAGS += -L$(LDPATH) -lcurse

SRCFILES=$(wildcard *.c)
OBJFILES=$(patsubst %.c,%.o,$(SRCFILES))
TARGET=curse_tester.out
all:	$(TARGET)

$(TARGET):	$(OBJFILES)
	$(CC)	$(CFLAGS) $(LDFLAGS) $^ -o $(TARGET)


*.o:	*.c
	$(CC) $(CFLAGS) $< -c

clean:
	$(RM) $(OBJFILES) $(TARGET)
