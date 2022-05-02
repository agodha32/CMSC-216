
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra
CC = gcc

all: d8sh

clean: 
	rm -f d8sh *.o

lexer.o: lexer.c
	$(CC) $(CFLAGS) -c lexer.c

parser.tab.o: parser.tab.c command.h
	$(CC) $(CFLAGS) -c parser.tab.c

executor.o: executor.c executor.h command.h
	$(CC) $(CFLAGS) -c executor.c

d8sh.o: d8sh.c executor.h lexer.h
	$(CC) $(CFLAGS) -c d8sh.c

d8sh: lexer.o parser.tab.o executor.o d8sh.o
	$(CC) $(CFLAGS) -lreadline -o d8sh lexer.o parser.tab.o executor.o d8sh.o
