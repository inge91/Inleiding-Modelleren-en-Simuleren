CC = gcc
CFLAGS = -std=c99 -g -Wall
LINKING_FLAGS = -Ignuplot_i/src -lm

default: all

all: tests malaria

tests: differentials.c tests.c
	$(CC) $(CFLAGS) $(LINKING_FLAGS) differentials.c tests.c gnuplot_i/gnuplot_i.o -o tests

malaria: differentials.c malaria.c
	$(CC) $(CFLAGS) $(LINKING_FLAGS) differentials.c malaria.c gnuplot_i/gnuplot_i.o -o malaria

clean:
	rm tests
	rm malaria
