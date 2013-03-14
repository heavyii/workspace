EXEC = thread_mutex
OBJS = thread_mutex.o
HEADERS = 

#CC = arm-linux-gcc
CC = gcc
INC = -I.
CFLAGS = ${INC}  -g 
CLDFLAGS = -lpthread

all:${EXEC}
${EXEC} : ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} ${CLDFLAGS}

${OBJS} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS} ${EXEC}

