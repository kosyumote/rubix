src=src/
build=build/

files=$(src)rubiks.cpp

flags=-O2 -g -Wall -Wextra -Werror
ldflags=-lGL -lGLEW -lglut -lGLU

.PHONY: all clean

all: $(build)rubiks

clean:
	rm $(build)*

$(build)rubiks: $(files)
	g++ $(flags) -o $@ $^ $(ldflags)
