cc=gcc
target=makemaze
objects=maze.o

$(target): $(objects)
	     $(cc) -o $(target) $(objects)

maze.o: maze.c
	$(cc) -c -o maze.o -g maze.c

.PHONY: clean

clean:
	rm $(target) $(objects)
