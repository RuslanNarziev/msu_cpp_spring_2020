CC = g++

all: test

test: test.o
	$(CC) -o test test.o --std=c++17 -pthread
	./test

test.o:
	$(CC) -c test.cpp task9.h task8.h --std=c++17 -pthread

clean:
	rm -rf *.o test
	rm -rf *.h.gch
	rm test_input
	rm test_output
