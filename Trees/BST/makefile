
all: Arvore

Arvore: ArvoreBinaria.o main.o
	gcc -o Arvore ArvoreBinaria.o main.o

ArvoreBinaria.o: ArvoreBinaria.c ArvoreBinaria.h
	gcc -c ArvoreBinaria.c -Wall -Werror -Wextra

main.o: main.c ArvoreBinaria.h
	gcc -c main.c -Wall -Werror -Wextra

clean:
	rm -rf *.o Arvore
