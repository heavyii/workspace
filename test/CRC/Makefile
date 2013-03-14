

CC=gcc
CFLAGS=-s

.SUFFIXES: .c .o

ALL = crc_test
all: $(ALL)

OBJ=	crc16.o\
	crc32.o\
	test_main.o\

crc_test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 
	
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $*.c
	
.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(ALL)
	
