FLAGS=-Wall -O2 -ansi -Wno-unused-result -lm

All: bridges.out order

bridges.out: main.o clista.o id.o vet_listas.o
	gcc -o bridges main.o clista.o id.o vet_listas.o

.SUFFIXES: .o .c

.c.o:
	gcc -c $*.c ${FLAGS}

order:
	rm -f *.o

clean: order
	rm -f bridges.out
