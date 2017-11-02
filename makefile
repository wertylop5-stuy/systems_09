dir: main.o dir_stuff.o
	gcc -o dir main.o dir_stuff.o
	make clean

main.o: main.c include/dir_stuff.h
	gcc -c main.c include/dir_stuff.h

dir_stuff: dir_stuff.c include/dir_stuff.h
	gcc -c dir_stuff.c include/dir_stuff.h

clean:
	rm *.o

run:
	./dir
