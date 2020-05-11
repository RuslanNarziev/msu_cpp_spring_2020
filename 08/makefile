CC=g++

all: test

test: test.o task8.o
	$(CC) -o test test.o task8.o --std=c++17 -pthread
	./test

test.o: test.cpp task8.h
	$(CC) -c test.cpp --std=c++17

task8.o: test.cpp task8.h
	$(CC) -c task8.cpp --std=c++17

clean:
	rm -rf *.o test