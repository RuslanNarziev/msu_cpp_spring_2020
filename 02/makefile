CC=g++

all: task2.o test1.o test2.o
	$(CC) -o test_with_beg/end test1.o task2.o
	$(CC) -o test_without_beg/end test2.o task2.o

test1.o:
	$(CC) -c test1.cpp task2.h

test2.o:
	$(CC) -c test2.cpp task2.h



test_with_beg/end:
	./test_with_beg/end

test_without_beg/end:
	./test_without_beg/end


test: 
	./test_with_beg/end
	./test_without_beg/end

clean:
	rm -rf *.o task2