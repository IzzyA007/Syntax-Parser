CC = gcc
CFLAGS = -Wall


all: dcooke_parser

dcooke_parser: front.o parser.o
	$(CC) $(CFLAGS) -o dcooke_parser front.o parser.o
parser.o: parser.c front.h parser.h
	$(CC) $(CFLAGS) -c parser.c
front.o: front.c front.h
	$(CC) $(CFLAGS) -c front.c



.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o dcooke_parser
