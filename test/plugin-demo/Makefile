

CC=gcc
CFLAGS=-s -Wall

.SUFFIXES: .c .o

ALL = plugin-demo ls.so
all: $(ALL)


PLUGIN_OBJ=plugin.o 
plugin-demo: $(PLUGIN_OBJ)
	$(CC) $(CFLAGS) -rdynamic -o $@ $^   -ldl
	
#Libraries exporting _init() and _fini() will want  to  be  compiled  as follows
LS_OBJ=ls.o
ls.so: $(LS_OBJ)
	gcc -shared -nostartfiles -o $@ $^
	
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $*.c
	
.PHONY: clean
clean:
	rm -f *.o
	rm -f $(ALL)
	