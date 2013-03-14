EXEC = thread_sem
OBJS = thread_sem.o
HEADERS = 

#CC = arm-linux-gcc
INC = -I.
CFLAGS = ${INC} -g 

all:${EXEC}
${EXEC} : ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} -lpthread 

${OBJS} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS} ${EXEC}