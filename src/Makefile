
CC = cc
#CFLAGS = -std=c99 -pedantic -Wall -O9
#CFLAGS = -std=c99 -pedantic -Wall -Ofast
CFLAGS = -std=c99 -pedantic -Wall -O2
# -funsigned-char make char unsigned
#CFLAGS = -std=c11 -mpopcnt -pedantic -Wall -O1
#CFLAGS =  -Wall -O3
#CFLAGS =  -Wall -O9
#CFLAGS = clang -O3  -funroll-loops

CCPP = g++
#CPPFLAGS = -std=c++11 -Wall -g -finput-charset=utf-8


all: utf8bench

clean:
	rm -rf *.o utf8bench

rebuild: clean all
 

utf8bench.o: 
	$(CC) $(CFLAGS) -c -o utf8bench.o utf8bench.c 

utf8bench: utf8bench.o 
	$(CC) $(CFLAGS) -o utf8bench utf8bench.o	
