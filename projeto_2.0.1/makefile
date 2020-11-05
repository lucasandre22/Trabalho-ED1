FLAGS=-Wall -O2 -ansi -Wno-unused-result

All: a.out order

a.out: main.o cllist.o problema.o
	gcc main.o cllist.o problema.o 

.SUFFIXES: .o .c

.c.o:
	gcc -c $*.c ${FLAGS}

order:
	rm -f *.o

clean: order
	rm -f a.out
