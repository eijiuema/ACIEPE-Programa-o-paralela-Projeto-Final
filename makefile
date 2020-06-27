all: main

main: simplexnoise.o
	g++ -o terrain_generator main.cpp simplexnoise.o -fopenmp

simplexnoise.o:
	g++ -c lib/simplexnoise.cpp