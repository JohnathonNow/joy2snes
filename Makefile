CCFLAGS=-lwiringPi -lpthread -O3 -funroll-loops
all: main

main: main.c
	gcc $^ ${CCFLAGS} -o $@

read: read.c
	gcc $^ ${CCFLAGS} -o $@

joy: joy.c
	gcc $^ ${CCFLAGS} -o $@

clean:
	rm -rf *.o read joy
