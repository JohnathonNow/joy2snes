all: read joy

read: read.c
	gcc $^ -lwiringPi -O3 -o $@
joy: joy.c
	gcc $^ -lpthread -O3 -o $@

clean:
	rm -rf *.o read joy
