.PHONY: all clean

all: a.out

forest.o: forest.c forest.h
	gcc -c forest.c -o forest.o

main.o: main.c forest.h
	gcc -c main.c -o main.o

a.out: main.o forest.o
	gcc main.o forest.o -o a.out

clean:
	rm -rf *.o
	rm a.out


