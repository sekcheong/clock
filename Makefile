CC = g++
CFLAGS = -g -Wall -framework OpenGL -framework GLUT

all: clock 

clock: clock.o
	$(CC) $(CFLAGS) -o clock clock.o

clock.o: clock.cpp
	$(CC) -c clock.cpp

clean:
	-rm -f clock clock.o
