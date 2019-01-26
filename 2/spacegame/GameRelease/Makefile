CC=g++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lm -lsfgui -ljsoncpp
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -o $@ $<
