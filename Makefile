src=src/
build=build/

files=$(src)rubiks.cpp

flags=-O2 -g -Wall
ldflags=-lGL -lGLEW -lglut

.PHONY: all clean

all: $(build)rubiks

clean:
	rm $(build)*

$(build)rubiks: $(files)
	g++ $(flags) -o $@ $^ $(ldflags)
