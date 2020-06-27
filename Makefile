# Makefile for the project.

# whole project + few independent programs
all: sem.o create post wait main shmemfile shmemptest


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
	gcc -o $@ $< -lpthread -lrt

# shmemptest is not part of the project and it works independently 
shmemptest: shmemptest.c shmempub.o shmempub.h
	gcc -o $@ $< shmempub.o -lpthread -lrt

# shmempub is not part of the project and it works independently 
shmempub.o: shmempub.c shmempub.h
	gcc -c -o $@ $< 


.PHONY: clean
clean:  
	-rm main post create wait sem.o shmemfile shmempub.o shmemptest mmapfile
