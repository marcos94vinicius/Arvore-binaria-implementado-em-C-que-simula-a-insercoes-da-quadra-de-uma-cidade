arvoreB.o: arvoreB.h arvoreB.c
	gcc -c arvoreB.c

arvoreRetangulo.o: arvoreRetangulo.h arvoreB.h arvoreRetangulo.c
	gcc -c arvoreRetangulo.c

bdrr: main.o arvoreB.o arvoreRetangulo.o
	gcc -o bdrr main.o arvoreB.o arvoreRetangulo.o

main.o: main.c
	gcc -c main.c
