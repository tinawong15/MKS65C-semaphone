all: main.o ctrl.o
	gcc ctrl.o -o control
	gcc main.o

main.o: main.c
	gcc -c main.c

ctrl.o: ctrl.c ctrl.h
	gcc -c ctrl.c

setup: ctrl.o
	./control $(args)

run:
	./a.out

clean:
	rm -rf *.o a.out control *.txt
