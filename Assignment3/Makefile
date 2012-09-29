CC = gcc
CFLAGS = -std=c99 -g -Wall
LINKING_FLAGS = -Ignuplot_i/src -lm

default: tests

tests:
	$(CC) $(CFLAGS) $(LINKING_FLAGS) differentials.c tests.c gnuplot_i/gnuplot_i.o -o tests
