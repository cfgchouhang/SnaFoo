all:snake
CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0`

snake : snake.o control.o set.o act.o draw.o
	$(CC) control.o set.o act.o draw.o snake.o $(CFLAGS) -o snake

snake.o : snake.c snake.h
	$(CC) -c snake.c $(CFLAGS) -o $@

set.o : set.c snake.h
	$(CC) -c set.c $(CFLAGS) -o $@

control.o : control.c snake.h
	$(CC) -c control.c $(CFLAGS) -o $@

act.o : act.c snake.h
	$(CC) -c act.c $(CFLAGS) -o $@

draw.o : draw.c snake.h
	$(CC) -c draw.c $(CFLAGS) -o $@

clean : 
	rm snake.o act.o set.o draw.o

