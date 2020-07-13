#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "Alocacao.h"

#define reset "\e[0m"

//define as cores das pecas
void DefinirCor(peca Peca){
  switch(Peca.numero){
    case '1':
      printf("\e[0;101m");
      break;

    case '2':
      printf("\e[0;102m");
      break;

    case '3':
      printf("\e[0;103m");
      break;

    case '4':
      printf("\e[0;104m");
      break;

    case '5':
      printf("\e[0;105m");
      break;

    case '6':
      printf("\e[0;106m");
      break;
  }
}

//atualiza o tabuleiro
peca **AtualizarTabuleiro(peca **Tabuleiro,int *tamV,int tamN){

  //realoca ponteiro do tabuleiro
  Tabuleiro = (peca **)realloc(Tabuleiro,sizeof(peca *)*tamN);
  VerifAlocacaoPPTab(Tabuleiro);

  //realoca os elementos do tabuleiro
  for(int i = 0;i<tamN;i++){
    Tabuleiro[i] = (peca *)realloc(Tabuleiro[i],sizeof(peca)*tamN);
    VerifAlocacaoPTab(Tabuleiro[i]);
  }

  //transfere os elementos para as novas posicoes
  for(int i = tamN-1;i>=0;i--){
    for(int j = tamN-1;j>=0;j--){
      if(Tabuleiro[i][j].letra >= 'A' && Tabuleiro[i][j].letra <= 'F'){

        //a nova linha equivale a i+(tamN-(*tamV))/2
        //a nova coluna equivale a j+(tamN-(*tamV))/2
        Tabuleiro[i+(tamN-(*tamV))/2][j+(tamN-(*tamV))/2].letra = Tabuleiro[i][j].letra;
        Tabuleiro[i][j].letra = ' ';
        Tabuleiro[i+(tamN-(*tamV))/2][j+(tamN-(*tamV))/2].numero = Tabuleiro[i][j].numero;
        Tabuleiro[i][j].numero = ' ';

      }
    }
  }

  //inicializa os novos elementos com espaco
  for(int i = 0;i<tamN;i++){
    for(int j = 0;j<tamN;j++){
      if(Tabuleiro[i][j].letra < 'A' || Tabuleiro[i][j].letra > 'F'){
        Tabuleiro[i][j].letra = ' ';
        Tabuleiro[i][j].numero = ' ';
      }
    }
  }
  return Tabuleiro;
}

//printa tabuleiro
void PrintarTabuleiro(peca **Tabuleiro,int *tam,int Altura[2],int Largura[2]){

  //printa coordenadas
  printf("    ");
  for(int i = Largura[0];i<=Largura[1];i++){
    if(i<0){
      printf("%d   ",i);
    } else {
      printf(" %d   ",i);
    }
  }
  printf("    \n");
  for(int i = Altura[0];i<=Altura[1];i++){
    if(i<0){
      printf("%d ",i);
    } else {
      printf(" %d ",i);
    }

    //separa colunas
    for(int j = Largura[0];j<=Largura[1];j++){
      printf("| ");
      DefinirCor(Tabuleiro[i+(*tam/2)][j+(*tam/2)]);
      printf("%c%c",Tabuleiro[i+(*tam/2)][j+(*tam/2)].letra,Tabuleiro[i+(*tam/2)][j+(*tam/2)].numero);
      printf("%s|",reset);
      
    }
    printf(" %d\n   ",i);

    //separa linhas
    for(int k = 0;k<=Largura[1]-Largura[0];k++){
      printf("-----");
    }
    printf("\n");

  }

  //printa coordenadas
  printf("    ");
  for(int i = Largura[0];i<=Largura[1];i++){
    if(i<0){
      printf("%d   ",i);
    } else {
      printf(" %d   ",i);
    }
  }
  printf("    \n");
}