CC = gcc
DEBUG = #-g -D__DEBUG__ -DPOX_MAGIC_LINE="\"./poshx\""
CFLAGS = -Wall -I./include $(DEBUG)
OBJECTS = main.o pox.o poxc.o error.o stack.o symtab.o

H_PREFIX = ./include
POSHX_H = $(H_PREFIX)/poshx.h
POX_H = $(H_PREFIX)/pox.h
POXC_H = $(H_PREFIX)/poxc.h
ERROR_H = $(H_PREFIX)/error.h
TYPE_H = $(H_PREFIX)/type.h
STACK_H = $(H_PREFIX)/stack.h
COMMON_H = $(H_PREFIX)/common.h
SYMTAB_H = $(H_PREFIX)/symtab.h

.PHONY: all clean cleanall all-clean

all: poshx
clean:
	rm *.o
cleanall: clean
	rm poshx
all-clean: all clean

poshx: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

$(POSHX_H): $(POX_H) $(POXC_H) $(ERROR_H) $(TYPE_H) $(STACK_H) $(COMMON_H)
main.o: main.c $(POSHX_H)
pox.o: pox.c $(POX_H) $(ERROR_H) $(TYPE_H) $(STACK_H) $(COMMON_H)
poxc.o: poxc.c $(POXC_H) $(ERROR_H) $(TYPE_H) $(SYMTAB_H)
error.o: error.c $(ERROR_H) $(TYPE_H)
stack.o: stack.c $(STACK_H) $(ERROR_H) $(TYPE_H)
symtab.o: symtab.c $(SYMTAB_H) $(TYPE_H) $(ERROR_H)

