FLAGS=-Wall -O2 -ansi -Wno-unused-result -lm

All: bridges.out order

bridges.out: main.o clista.o monta_caminho.o vet_listas.o mapeamento_localidades.o
	gcc -o bridges main.o clista.o monta_caminho.o vet_listas.o mapeamento_localidades.o

.SUFFIXES: .o .c

.c.o:
	gcc -c $*.c ${FLAGS}

order:
	rm -f *.o

clean: order
	rm -f bridges.out
