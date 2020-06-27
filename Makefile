

all: sem.o create post main wait



sem.o: sem.c sem.h
	gcc -c -o sem.o sem.c


wait: wait.c sem.o sem.h
	gcc -o $@ $^ -lpthread


create: create.c sem.o sem.h
	gcc -o $@ $^ -lpthread


post: post.c sem.o sem.h
	gcc -o $@ $^ -lpthread


main: main.c
	gcc -o $@ $^ -lpthread -lrt


.PHONY: clean
clean:  
	-rm main post create wait sem.o

