CC		= gcc
LDFLAGS	= -I./include
CFLAGS	= -I./include -D__DEBUG__

pox: main.c pox.o

pox.o: pox.c ./include/pox.h ./include/error.h ./include/types.h ./include/stack.h

pox_gen: pox_gen.c
	gcc -o pox_gen pox_gen.c
	./pox_gen
	./pox test.pox
