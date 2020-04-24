CC=g++

all: test

test: test.o task7.h
	$(CC) -o test test.cpp
	./test

clean:
	-rm test test.o 
	-rm -rf *.h.gch