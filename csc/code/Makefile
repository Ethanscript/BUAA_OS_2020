.PHONY:clean

all:fibo

fibo:main.o fibo.o
	gcc -o ../fibo fibo.o main.o
fibo.o:fibo.c
	gcc -c  fibo.c -o fibo.o -I../include -lm
main.o: main.c
	gcc -c main.c -o main.o -I../include -lm
clean:
	rm fibo.o main.o
	
