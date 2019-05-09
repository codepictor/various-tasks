.PHONY: clean all

all: matrix

main.o: main.cpp matrix.h profile.h
	g++ -c main.cpp --std=c++1z -DNDEBUG -O3 -o main.o

matrix.o: matrix.cpp matrix.h profile.h
	g++ -c matrix.cpp --std=c++1z -DNDEBUG -O3 -o matrix.o

profile.o: profile.cpp profile.h
	g++ -c profile.cpp --std=c++1z -DNDEBUG -O3 -o profile.o

matrix: main.o matrix.o profile.o
	g++ main.o matrix.o profile.o -O3 -lpthread -o matrix

clean:
	rm -rf *.o
	rm matrix

