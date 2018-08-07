CFLAGS= -Wall -c

all: compile

compile:
	gcc -c ./src/main.c -o ./obj/output.o
	gcc -o ./testing/os ./obj/output.o

clean:
	-rm -f ./obj/*.o
	-rm -rf ./testing/*
	clear
