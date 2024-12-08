# Top level directories: include, src, lib
# This file goes in the src directory

IDIR =../include
CC=gcc
CFLAGS=-Wall -Werror -Wno-unused-function -I$(IDIR)
VALGRIND_ARGS=--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose\
		   --log-file=valgrind-out.txt

ODIR=obj
LDIR=../lib

LIBS=

_DEPS = vec.h
DEPS  = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ  = main.o
OBJ   = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

main: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ -g

# create object file directory if not existing
# (src/obj)
$(ODIR):
	mkdir -p $(ODIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ *.o core $(INCDIR)/*~

run: main
	./main

mem: main
	valgrind $(VALGRIND_ARGS) ./main

debug: main
	gdb ./main
