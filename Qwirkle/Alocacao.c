#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"

//verifica alocacao de ponteiro do tipo dados
void VerifAlocacaoPDados(dados *ponteiro){
  if(ponteiro == NULL){
    printf("Erro de alocaçao!!\n");
    exit(0);
  }
}

//verifica alocacao de ponteiro de ponteiro do tipo peca
void VerifAlocacaoPPTab(peca **ponteiro){
  if(ponteiro == NULL){
    printf("Erro de alocaçao!!\n");
    exit(0);
  }
}

//verifica alocacao de ponteiro do tipo peca
void VerifAlocacaoPTab(peca *ponteiro){
  if(ponteiro == NULL){
    printf("Erro de alocaçao!!\n");
    exit(0);
  }
}

//libera os ponteiros
void LiberarMemoria(dados *Jogador,int Njogadores,peca **Tabuleiro,int *tam,peca **PecasRestantes,int *qPecasRestantes,int *Ptemp){
  
  free(Jogador);
  for(int i = 0;i<*tam;i++){
    free(Tabuleiro[i]);
  }
  free(Tabuleiro);

  for(int i = 0;i<18;i++){
    free(PecasRestantes[i]);
  }
  free(PecasRestantes);
  free(qPecasRestantes);
  free(Ptemp);
}