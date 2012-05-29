
CC=gcc-4.4
LDPATH=../lib

CFLAGS += -I../include/
LDFLAGS += -L$(LDPATH) -lcurse -lrt
LD_LIBRARY_PATH += $(LDPATH)

SRCFILES=$(wildcard *.c)
OBJFILES=$(patsubst %.c,%.o,$(SRCFILES))
TARGET=test1.out
all:	$(TARGET)

$(TARGET):	$(OBJFILES)
	$(CC)	$(CFLAGS) $(LDFLAGS) $^ -o $(TARGET)


*.o:	*.c
	$(CC) $(CFLAGS) $< -c

clean:
	$(RM) $(OBJFILES) $(TARGET)
