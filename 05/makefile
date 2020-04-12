CC=g++

all: task5.o test1.o test2.o test3.o
	$(CC) -o input_output test1.o task5.o
	$(CC) -o add_sub test2.o task5.o
	$(CC) -o comparison test3.o task5.o

test1.o:
	$(CC) -c test1.cpp task5.h

test2.o:
	$(CC) -c test2.cpp task5.h

test3.o:
	$(CC) -c test3.cpp task5.h




input_output:
	./input_output

test_err:
	./add_sub

comparison:
	./comparison

test: 
	./input_output
	./add_sub
	./comparison

clean:
	rm -rf *.o task5