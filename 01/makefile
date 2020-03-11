CC=g++

all: task1.o test1.o test2.o test3.o
	$(CC) -o test_make_alloc test1.o task1.o
	$(CC) -o test_alloc test2.o task1.o
	$(CC) -o test_reset test3.o task1.o

test1.o:
	$(CC) -c test1.cpp task1.h

test2.o:
	$(CC) -c test2.cpp task1.h

test3.o:
	$(CC) -c test3.cpp task1.h


test_make_alloc:
	./test_make_alloc

test_alloc:
	./test_alloc

test_reset:
	./test_reset

test: 
	./test_alloc
	./test_make_alloc
	./test_reset

clean:
	rm -rf *.o task1