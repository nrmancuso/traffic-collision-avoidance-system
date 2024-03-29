SHELL := /bin/bash
# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = tcas

# file types to clean
FILE_TYPES_TO_CLEAN = *.exec *~ *.gcov *.gcda *.gcno *.out *.html *.css

all: $(TARGET).exec

$(TARGET).exec: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).exec $(TARGET).c

test: $(TARGET).c
	$(info "Running test suite #1 for predicate coverage...")
	$(CC) -fprofile-arcs -ftest-coverage -o $(TARGET).exec $(TARGET).c
	# Test Suite #1, predicate coverage
	./$(TARGET).exec 0 0 0 0 0 0 7 8 9 10 11 12
	./$(TARGET).exec 700 1 1 0 1 1 0 500 100 0 0 0
	./$(TARGET).exec 700 1 1 0 1 1 1 500 100 0 0 0
	./$(TARGET).exec 700 1 1 1 1 0 1 500 100 1 1 1
	./$(TARGET).exec 700 1 1 1 1 0 2 100 500 0 0 0
	./$(TARGET).exec 700 1 1 1 1 0 3 100 500 0 0 0
	./$(TARGET).exec 50 1 1 1 1 0 3 100 500 1 1 1


	gcov -b $(TARGET).exec-$(TARGET).gcno
	gcovr -r . --html --html-details -o predicate_coverage.html

	make clean
		
	$(CC) -fprofile-arcs -ftest-coverage -o $(TARGET).exec $(TARGET).c
	# Test Suite #2, ACC
	./$(TARGET).exec 700 1 1 0 1 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 700 1 1 0 1 1 0 500 100 0 0 0
	./$(TARGET).exec 700 1 1 3 1 1 0 60000 34567 0 0 34568

	./$(TARGET).exec 700 1 1 1 1 0 3 100 500 0 0 0
	./$(TARGET).exec 700 1 1 1 1 0 3 -1 500 0 0 0
	#./$(TARGET).exec 299 1 1 1 1 0 3 100 500 0 0 0
	 ./$(TARGET).exec 700 1 1 -1 1 0 3 100 500 0 0 0

	./$(TARGET).exec 0 1 1 0 1 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 700 1 1 0 1 1 0 500 100 0 0 0
	./$(TARGET).exec 0 1 1 0 1 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 700 1 1 3 1 1 0 60000 34567 0 0 34568

	./$(TARGET).exec 700 1 1 3 1 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 0 1 1 0 1 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 700 1 1 700 700 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 700 0 1 3 1 1 0 60000 34567 0 0 34568

	./$(TARGET).exec 700 0 1 3 1 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 50 1 1 1 1 0 3 100 500 1 1 1
	./$(TARGET).exec 700 0 0 3 1 1 0 60000 34567 0 0 34568

	./$(TARGET).exec 700 1 1 0 1 1 0 500 100 0 0 0
	./$(TARGET).exec 700 1 1 3 1 1 0 60000 34567 0 0 34568
	./$(TARGET).exec 700 1 1 -1 1 0 3 100 500 0 0 0

	./$(TARGET).exec 700 1 1 -1 1 0 3 100 500 0 0 0
	./$(TARGET).exec 0 1 1 0 1 1 0 60000 34567 0 1 34568
	./$(TARGET).exec 700 1 1 -1 1 0 3 100 500 0 0 0
	./$(TARGET).exec 700 1 1 -1 1 0 3 100 500 1 -1 0

	# from above, to get single clause ACC (same as predicate coverage for single clauses)
	./$(TARGET).exec 700 1 1 0 1 1 0 500 100 0 0 0
	./$(TARGET).exec 700 1 1 0 1 1 1 500 100 0 0 0
	./$(TARGET).exec 700 1 1 1 1 0 1 500 100 1 1 1
	./$(TARGET).exec 700 1 1 1 1 0 2 100 500 0 0 0
	./$(TARGET).exec 700 1 1 1 1 0 3 100 500 0 0 0
	./$(TARGET).exec 50 1 1 1 1 0 3 100 500 1 1 1
	./$(TARGET).exec 0 0 0 0 0 0 7 8 9 10 11 12

	gcov -b $(TARGET).exec-$(TARGET).gcno
	gcovr -r . --html --html-details -o predicate_coverage.html

clean:
	$(RM) $(FILE_TYPES_TO_CLEAN)

.PHONY: all test clean
