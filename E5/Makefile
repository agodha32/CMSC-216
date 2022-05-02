# provide a makefile with a target called shell_jr that 
# creates the executable shell_jr

CC = gcc
CFLAGS= -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -fstack-protector-all -pedantic-errors 

shell_jr: shell_jr.c
	$(CC) $(CFLAGS) shell_jr.c -o shell_jr

clean:
	rm -f shell_jr
