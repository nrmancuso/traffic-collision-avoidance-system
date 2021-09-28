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
FILE_TYPES_TO_CLEAN = *.exec *~ *.gcov *.gcda *.gcno *.out

all: $(TARGET).exec

$(TARGET).exec: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).exec $(TARGET).c

test: $(TARGET).c
	$(info "Running test suite...")
	$(CC) -fprofile-arcs -ftest-coverage -o $(TARGET).exec $(TARGET).c
	# Add test cases below
	./$(TARGET).exec 0 0 0 0 0 0 7 8 9 10 11 12
	./$(TARGET).exec 0 0 0 0 0 0 0 8 9 10 11 12
	./$(TARGET).exec 0 0 0 0 0 0 1 8 9 10 11 12
	./$(TARGET).exec 0 0 0 0 0 0 2 8 9 10 11 12
	./$(TARGET).exec 0 0 0 0 0 0 3 8 9 10 11 12
	./$(TARGET).exec 0 0 0 0 0 0 4 8 9 10 11 12
	#./$(TARGET).exec 
	#./$(TARGET).exec
	#./$(TARGET).exec 
	gcov -b $(TARGET).exec-$(TARGET).gcno

clean:
	$(RM) $(FILE_TYPES_TO_CLEAN)

.PHONY: all test clean
