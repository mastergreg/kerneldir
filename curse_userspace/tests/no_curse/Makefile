
CC=gcc-4.4
LDPATH=../../lib

CFLAGS += -I../../include/ 
LDFLAGS += -L $(LDPATH) -lcurse -lrt 

SRCFILES=$(wildcard *.c)
OBJFILES=$(patsubst %.c,%.o,$(SRCFILES))
TARGET=no_curse_test.out
all:	$(TARGET)

$(TARGET):	$(OBJFILES)
	$(CC)	$(CFLAGS) $(LDFLAGS) $^ -o $(TARGET)


*.o:	*.c
	$(CC) $(CFLAGS) $< -c

clean:
	$(RM) $(OBJFILES) $(TARGET)
