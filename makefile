CC = gcc
DEBUG = -g -D__DEBUG__
CFLAGS = -Wall -I./include $(DEBUG)
OBJECTS = main.o pox.o poxc.o error.o stack.o

H_PREFIX = ./include
POSHX_H = $(H_PREFIX)/poshx.h
POX_H = $(H_PREFIX)/pox.h
POXC_H = $(H_PREFIX)/poxc.h
ERROR_H = $(H_PREFIX)/error.h
TYPE_H = $(H_PREFIX)/type.h
STACK_H = $(H_PREFIX)/stack.h
COMMON_H = $(H_PREFIX)/common.h

.PHONY: all clean all-clean

debug: all
	./poshx sameout.pox

all: poshx
clean:
	rm *.o
	rm poshx
all-clean: all clean

poshx: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

$(POSHX_H): $(POX_H) $(POXC_H) $(ERROR_H) $(TYPE_H) $(STACK_H) $(COMMON_H)
main.o: main.c $(POSHX_H)
pox.o: pox.c $(POX_H) $(ERROR_H) $(TYPE_H) $(STACK_H) $(COMMON_H)
poxc.o: poxc.c $(POXC_H) $(ERROR_H) $(TYPE_H)
error.o: error.c $(ERROR_H) $(TYPE_H)
stack.o: stack.c $(STACK_H) $(ERROR_H) $(TYPE_H)

