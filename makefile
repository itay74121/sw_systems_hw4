all: frequency

frequency: frequency.o treelib.a
	gcc -Wall -g frequency.o treelib.a -o frequency


frequency.o: frequency.c
	gcc -Wall -g -c frequency.c 


treelib.a: treefuncs.o
	ar -rcs treelib.a treefuncs.o

treefuncs.o: tree.h treefuncs.c
	gcc -Wall -g -c treefuncs.c

clean:
	rm *.o *.a frequency

