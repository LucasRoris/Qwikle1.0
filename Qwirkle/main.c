//inclusao das bibliotecas e cabecalhos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Struct.h"
#include "Alocacao.h"
#include "Tabuleiro.h"
#include "Jogo.h"

#define reset "\e[0m"


int main(void) {

  //evita repeticoes no rand
  srand((unsigned)time(NULL));

  //limpa a tela
  system("clear||clr");

  //le o numero de jogadores
  int Njogadores;
  printf("Numero de jogadores: ");
  scanf("%d",&Njogadores);

  //inicializa (aloca e verifica) o vetor jogador do tipo dados
  dados *Jogador;
  Jogador = (dados *)malloc(sizeof(dados)*Njogadores);
  VerifAlocacaoPDados(Jogador);

  //le os nomes dos jogadores
  for(int i = 0;i<Njogadores;i++){
    printf("Jogador %d: ",i+1);
    setbuf(stdin,NULL);
    fgets(Jogador[i].nome,20,stdin);
    Jogador[i].pontos = 0;
    Jogador[i].qpecas = 0;
  }

  //le a opcao modo cheat
  printf("Digite S para Cheat Mode ou pressione outra tecla para modo normal: ");
  int cheat = 0;
  if(getchar() == 'S'){
    printf("Voce ativou o modo cheat!\n");
    cheat = 1;
  }

  //instrui o usuario
  while(getchar() != '\n');
  Instrucoes();

  //define a dimensao inicial do tabuleiro
  int Altura[2] = {0,0};
  int Largura[2] = {0,0};
  int *tam = NULL;
  tam = (int *)realloc(tam,sizeof(int));
  *tam = 0;

  //inicializa e apresenta o ponteiro representante do tabuleiro
  peca **Tabuleiro = NULL;
  Tabuleiro = AtualizarTabuleiro(Tabuleiro,tam,(*tam+10));
  *tam = *tam + 10;
  PrintarTabuleiro(Tabuleiro,tam,Altura,Largura);
  
  //inicializa o ponteiro de pecas restantes do jogo
  peca **PecasRestantes;
  PecasRestantes = (peca **)malloc(sizeof(peca *)*18);
  VerifAlocacaoPPTab(PecasRestantes);
  for(int i = 0;i<18;i++){
    PecasRestantes[i] = (peca *)malloc(sizeof(peca)*6);
    VerifAlocacaoPTab(PecasRestantes[i]);
  }
  InicializarPecasRestantes(PecasRestantes);

  //inicializa a quantidade de pecas do jogo
  int *qPecasRestantes;
  qPecasRestantes = (int *)malloc(sizeof(int));
  *qPecasRestantes = 108;

  //inicializa o ponteiro de pontos temporarios
  int *Ptemp = (int *)malloc(sizeof(int));

  //laco que mantem o jogo
  while(*qPecasRestantes != 0){

    //laco que mantem as rodadas
    for(int i = 0;i<Njogadores;i++){

      //sorteio de pecas
      SortearPecas(Jogador,i,PecasRestantes,qPecasRestantes);
      
      //variavel que define quantas vezes o jogador ja inseriu pecas
      int jogadas = 1;

      //vetor que contem as possibilidades de jogada
      int possibilidades[4] = {100,0,0,0};

      *Ptemp = 0;

      //laco que mantem a jogada
      int flag = 0;
      while(flag == 0){
        //laco para tratamento de entrada invalida
        int ok = 1;
        while(ok == 1){
        //apresentacao das pecas e do nome do jogador
        printf("Jogada de %s",Jogador[i].nome);
        printf("Pecas disponiveis : ");
        for(int j = 0;j<Jogador[i].qpecas;j++){
          DefinirCor(Jogador[i].pecas[j]);
          printf("%c%c",Jogador[i].pecas[j].letra,Jogador[i].pecas[j].numero);
          printf("%s ",reset);
        }

        

          //apresenta as opcoes
          if(jogadas > 1){
            printf("\nOpcoes : jogar, passar\n");
          } else {
            printf("\nOpcoes : jogar, trocar, passar\n");
          }

          //le a opcao
          char jogada[30];
          setbuf(stdin,NULL);
          fgets(jogada, 30 , stdin);

          system("clr||clear");

          //verifica e insere a peca
          if(jogada[0] == 'j' && jogada[1] == 'o' && jogada[2] == 'g' && jogada[3] == 'a' && jogada[4] == 'r' && jogada[5] == ' '){
            Tabuleiro = Jogada(Jogador,i,Tabuleiro,tam,Largura,Altura,cheat,possibilidades,Ptemp,jogada);
            ok = 0;
            jogadas++;
          }

          //verifica a troca as pecas
          else if(jogada[0] == 't' && jogada[1] == 'r' && jogada[2] == 'o' && jogada[3] == 'c' && jogada[4] == 'a' && jogada[5] == 'r'){
            if(jogadas == 1){
              ok = TrocarPeca(Jogador,i,PecasRestantes,qPecasRestantes,jogada);
              if(ok ==1){
                printf("Entrada Invalida!\n");
              }
              flag = 1;
            } else {
              printf("Voce nao pode trocar mais suas pecas!\n");
            }
            
          }

          //passsa o turno
          else if(strcmp(jogada,"passar\n") == 0){
            flag = 1;
            ok = 0;
          }

          //trata entrada invalida
          else{
            printf("Escolha invalida!\n");
          }
          //apresenta situacao atual do tabuleiro
          PrintarTabuleiro(Tabuleiro,tam,Altura,Largura);
        }

        
        
      }

      //acumula os pontos
      Jogador[i].pontos += *Ptemp;

      //apresenta pontuacao
      printf("=======\nPontuacao = %d\nPontuacao acumulada = %d\n=======\n",*Ptemp,Jogador[i].pontos);
    }
  }

  //calcula vencedor
  int max = 0;
  int ganhador = 0;
  for(int i = 0;i<Njogadores;i++){  
    if(Jogador[i].pontos > max){
      max = Jogador[i].pontos;
      ganhador = i;
    }
  }

  //apresenta vencedor
  printf("Vencedor %s",Jogador[ganhador].nome);

  //libera ponteiros
  LiberarMemoria(Jogador,Njogadores,Tabuleiro,tam,PecasRestantes,qPecasRestantes,Ptemp);
}