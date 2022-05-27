phony: build

run: tema
	./tema

build : test.o tree.o list.o
	gcc -o tema test.o tree.o list.o

test.o: test.c
	gcc -g -c test.c

tree.o: tree.c
	gcc -g -c tree.c

list.o: list.c
	gcc -g -c list.c

clean:
	rm *.o tema