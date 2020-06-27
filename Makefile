# Makefile for the project.

# whole project + few independent programs
all: sem.o create post wait main shmemfile



sem.o: sem.c sem.h
	gcc -c -o sem.o sem.c


wait: wait.c sem.o sem.h
	gcc -o $@ $^ -lpthread


create: create.c sem.o sem.h
	gcc -o $@ $^ -lpthread


post: post.c sem.o sem.h
	gcc -o $@ $^ -lpthread

# main is not part of the project and it works independently 
main: main.c
	gcc -o $@ $^ -lpthread -lrt

# shmemfile is not part of the project and it works independently 
shmemfile: shmemfile.c
	gcc -o $@ $^ -lpthread -lrt

# shmempub is not part of the project and it works independently 
shmempub: shmempub.c
	gcc -o $@ $^ -lpthread -lrt


.PHONY: clean
clean:  
	-rm main post create wait sem.o shmemfile shmempub
