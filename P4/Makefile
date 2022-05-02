
CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra

calendar.o: calendar.c calendar.h
	$(CC) $(CFLAGS) -c calendar.c

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
	$(CC) $(CFLAGS) -c my_memory_checker_216.c

all: public01 public02 public03 public04 public05 public06 student_tests

public01.o: public01.c event.h calendar.h
	$(CC) $(CFLAGS) -c public01.c

public01: calendar.o my_memory_checker_216.o public01.o
	$(CC) calendar.o my_memory_checker_216.o public01.o -o public01

public02.o: public02.c event.h calendar.h
	$(CC) $(CFLAGS) -c public02.c

public02: calendar.o my_memory_checker_216.o public02.o
	$(CC) calendar.o my_memory_checker_216.o public02.o -o public02

public03.o: public03.c event.h calendar.h
	$(CC) $(CFLAGS) -c public03.c

public03: calendar.o my_memory_checker_216.o public03.o
	$(CC) calendar.o my_memory_checker_216.o public03.o -o public03

public04.o: public04.c event.h calendar.h
	$(CC) $(CFLAGS) -c public04.c

public04: calendar.o my_memory_checker_216.o public04.o
	$(CC) calendar.o my_memory_checker_216.o public04.o -o public04

public05.o: public05.c event.h calendar.h
	$(CC) $(CFLAGS) -c public05.c

public05: calendar.o my_memory_checker_216.o public05.o
	$(CC) calendar.o my_memory_checker_216.o public01.o -o public05

public06.o: public06.c event.h calendar.h
	$(CC) $(CFLAGS) -c public06.c

public06: calendar.o my_memory_checker_216.o public06.o
	$(CC) calendar.o my_memory_checker_216.o public06.o -o public06

student_tests.o: student_tests.c event.h calendar.h
	$(CC) $(CFLAGS) -c student_tests.c

student_tests: calendar.o my_memory_checker_216.o student_tests.o
	$(CC) calendar.o my_memory_checker_216.o student_tests.o -o student_tests

clean: 
	rm -f *.o public01 public02 public03 public04 public05 public06 student_tests

