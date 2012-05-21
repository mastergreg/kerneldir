
SRCFILES=$(wildcard *.c)
OBJFILES=$(patsubst %.c,%.o,$(SRCFILES))
TARGET=curse_tester.out
all:	$(TARGET)

$(TARGET):	$(OBJFILES)
	$(CC)	$^ -o $(TARGET)


*.o:	*.c
	$(CC) $< -c

clean:
	$(RM) $(OBJFILES) $(TARGET)
