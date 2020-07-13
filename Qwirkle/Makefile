all: main

run: main
	./main

Alocacao.o: Alocacao.c
	gcc -o Alocacao.o -c Alocacao.c

Jogo.o: Jogo.c
	gcc -o Jogo.o -c Jogo.c

MoviValido.o: MoviValido.c
	gcc -o MoviValido.o -c MoviValido.c

Tabuleiro.o: Tabuleiro.c
	gcc -o Tabuleiro.o -c Tabuleiro.c

main.o: main.c
	gcc -o main.o -c main.c

main: main.o Alocacao.o Tabuleiro.o Jogo.o MoviValido.o
	gcc -o main main.o Alocacao.o Tabuleiro.o Jogo.o MoviValido.o
	
clean:
	@rm *.o