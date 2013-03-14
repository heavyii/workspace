

CC=gcc
CFLAGS=-s

.SUFFIXES: .c .o

ALL = longopt
all: $(ALL)

OBJ=longopt.o

longopt: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 
	
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $*.c
	
.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(ALL)
	