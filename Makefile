# Makefile
CC = gcc -std=c99 -pedantic -Wall -Wextra
trekisteri: main.o linkitettylista.o
	$(CC) -o trekisteri main.o linkitettylista.o
linkitettylista.o: linkitettylista.c linkitettylista.h
	$(CC) -c linkitettylista.c
main.o: main.c linkitettylista.h
	$(CC) -c main.c

