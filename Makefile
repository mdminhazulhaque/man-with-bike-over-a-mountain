# Makefile written by Minhazul Haque
# mdminhazulhaque@gmail.com

GLLIBS=-lGL -lGLU -lglut -lm

default:
	g++ -Wall -o mountain mountain.cpp $(GLLIBS)
	rm -f *.o

clean:
	rm -f *.o