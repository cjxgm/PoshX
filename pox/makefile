CC		= gcc
LDFLAGS	= -I../include -I./include
CFLAGS	= -I../include -I./include# -D__DEBUG__

pox: main.c pox.o stack.o

pox.o: pox.c ./include/pox.h ./include/stack.h ../include/error.h ../include/type.h ../include/opcode.h ../include/const.h

stack.o: stack.c ./include/stack.h ../include/type.h

pox_gen: pox_gen.c
	gcc $(CFLAGS) -o pox_gen pox_gen.c
	./pox_gen
	chmod +x test.pox

