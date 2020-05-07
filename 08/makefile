CC=g++

all: test

test: test.o
	$(CC) -o test test.o --std=c++17 -pthread
	./test

test.o: test.cpp task8.h
	$(CC) -c test.cpp --std=c++17

clean:
	rm -rf *.o test