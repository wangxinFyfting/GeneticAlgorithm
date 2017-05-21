CC = gcc
all:ga_test
ga_test:main.c GA.c
	$(CC) main.c GA.c -o ga_test
clean:
	-rm ga_test