CC		= gcc
LDFLAGS	= -I../include -I./include
CFLAGS	= -I../include -I./include -D__DEBUG__

poxc: main.c poxc.o

poxc.o: poxc.c ./include/poxc.h ../include/type.h ../include/opcode.h ../include/error.h ../include/const.h

