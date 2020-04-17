CC=g++

all: test


test1.o:
	$(CC) -c test1.cpp task6.h

test2.o:
	$(CC) -c test2.cpp task6.h

test3.o:
	$(CC) -c test3.cpp task6.h

test1: test1.o
	$(CC) -o test1 test1.o task6.h

test1: test1.o
	$(CC) -o test2 test2.o task6.h

test1: test1.o
	$(CC) -o test3 test3.o task6.h

test: test1 test2 test3
	./test1
	./test2
	./test3

clean:
	rm -rf *.h.gch task6
	rm -rf *.o task6