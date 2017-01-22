#******************************************************************************
## Function name: Makefile
##
## DESCRIPTION:   A set of commands to compile all files in project1
##
## Parameters:    n/a
##
## Return values: n/a
##
##*****************************************************************************

# Declare the variables
CC = gcc

CFLAGS = -c

# This target will compile all the files
all: hello

# This target will compile all the files
hello: main.o iofunctions.o getaddress.o dbfunctions.c
	$(CC) -o project1 main.o iofunctions.o getaddress.o dbfunctions.c

# This target will compile main.o only
main.o: main.c
	$(CC) $(CFLAGS) main.c

# This target will compile address.o only
getaddress.o: getaddress.c
	$(CC) $(CFLAGS) getaddress.c

# This target will compile dbfunctions.o only
dbfunctions.o: dbfunctions.c
	$(CC) $(CFLAGS) dbfunctions.c

# This target will compile iofunctions.o only
iofunctions.o: iofunctions.c
	$(CC) $(CFLAGS) iofunctions.c

# This target will remove the executable and all object files
clean:
	rm -rf *o project1


