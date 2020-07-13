#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"

//verifica se a jogada respeita as regras do jogo
int AuxMovimentoValido(int flag,peca **Tabuleiro,peca PecaJogada,int x,int auxX,int y,int auxY,int possibilidades[4]){

  //verifica se os caracteres sao validos
  if(Tabuleiro[x+auxX*2][y+auxY*2].letra >= 'A' && Tabuleiro[x+auxX*2][y+auxY*2].letra <= 'F'){

    //verifica se a peca adjacente esta em sequencia de letras
    if(Tabuleiro[x+auxX*2][y+auxY*2].letra == Tabuleiro[x+auxX][y+auxY].letra){ 
      
      //verifica compatibilidade da peca jogada
      if(PecaJogada.letra == Tabuleiro[x+auxX][y+auxY].letra){
        int i = 0;
        int j = 0;
         while(Tabuleiro[x+auxX+i][y+auxY+j].numero >= '1' && Tabuleiro[x+auxX+i][y+auxY+j].numero <= '6'){
          if(Tabuleiro[x+auxX+i][y+auxY+j].numero == PecaJogada.numero){
            flag = 0;
            break;
          }
          if(auxX>0){
            i++;
          }
          if(auxX<0){
            i--;
          }
          if(auxY>0){
            j++;
          }
          if(auxY<0){
            j--;
          }
         }

        //atualiza possibilidades
        possibilidades[2] = x+auxX+i;
        possibilidades[3] = y+auxY+j;

      } else {
        flag = 0;
      }

    }

    //verifica se a peca adjacente esta em sequencia de numeros
    else {

      //verifica compatibilidade da peca jogada
      if(PecaJogada.numero == Tabuleiro[x+auxX][y+auxY].numero){
        int i = 0;
        int j = 0;
        while(Tabuleiro[x+auxX+i][y+auxY+j].letra >= 'A' && Tabuleiro[x+auxX+i][y+auxY+j].letra <= 'F'){

          if(Tabuleiro[x+auxX+i][y+auxY+j].letra == PecaJogada.letra){
            flag = 0;
            break;
          }
          if(auxX>0){
            i++;
          }
          if(auxX<0){
            i--;
          }
          if(auxY>0){
            j++;
          }
          if(auxY<0){
            j--;
          }
        }

        //atualiza possibilidades
        possibilidades[2] = x+auxX+i;
        possibilidades[3] = y+auxY+j;

      } else {
        flag = 0;
      }

    }
  } 

  //verifica o caso de a peca adjacente ainda nao estar em sequencia (sozinha)
  else {

    //verifica compatibilidade da peca jogada
    if(PecaJogada.letra == Tabuleiro[x+auxX][y+auxY].letra && PecaJogada.numero == Tabuleiro[x+auxX][y+auxY].numero){
      flag = 0;
    } else {
      if(PecaJogada.letra != Tabuleiro[x+auxX][y+auxY].letra && PecaJogada.numero != Tabuleiro[x+auxX][y+auxY].numero){
        flag = 0;
      } else {
        possibilidades[2] = x+auxX*2;
        possibilidades[3] = y+auxY*2;
      }
    }
  }
  return flag;
}

int MovimentoValido(peca **Tabuleiro,peca PecaJogada,int x,int y,int Jogada,int *tam,int possibilidades[4]){

  int flag = 1;
  int count = 0;

  //verifica se a posicao escolhida esta desocupada
  if(Tabuleiro[x][y].letra != ' '){
    return 0;
  }

  //verifica se eh a primeira colocacao (coordenada 0 0)
  if(Tabuleiro[*tam/2][*tam/2].letra == ' ' && x == *tam/2 && y == *tam/2){
    return 1;
  }

  //verifica se as regras estao satisfeitas a partir da funcao auxmovimento valido
  //repete o procedimento para todos os elementos que a nova peca encosta
  if(((possibilidades[0] == x && possibilidades[1] == y) || (possibilidades[2] == x && possibilidades[3] == y)) || possibilidades[0] >= 100){
    if(Tabuleiro[x+1][y].letra >= 'A' && Tabuleiro[x+1][y].letra <= 'F'){
      flag = AuxMovimentoValido(flag,Tabuleiro,PecaJogada,x,1,y,0,possibilidades);
      if(flag == 1){

        //atualiza possibilidades
        possibilidades[0] = x-1;
        possibilidades[1] = y;
      }
    } 
    else {
    count++;
  }

  if(Tabuleiro[x-1][y].letra >= 'A' && Tabuleiro[x-1][y].letra <= 'F'){
    flag = AuxMovimentoValido(flag,Tabuleiro,PecaJogada,x,-1,y,0,possibilidades);
    if(flag == 1){
      //atualiza possibilidades
      possibilidades[0] = x+1;
      possibilidades[1] = y;
    }
  } else {
    count++;
  }


  if(Tabuleiro[x][y+1].letra >= 'A' && Tabuleiro[x][y+1].letra <= 'F'){
    flag = AuxMovimentoValido(flag,Tabuleiro,PecaJogada,x,0,y,1,possibilidades);
    if(flag == 1){
      //atualiza possibilidades
      possibilidades[0] = x;
      possibilidades[1] = y-1;
    }
  } else {
    count++;
  }

  if(Tabuleiro[x][y-1].letra >= 'A' && Tabuleiro[x][y-1].letra <= 'F'){
    flag = AuxMovimentoValido(flag,Tabuleiro,PecaJogada,x,0,y,-1,possibilidades);
    if(flag == 1){
      //atualiza possibilidades
      possibilidades[0] = x;
      possibilidades[1] = y+1;
    }
  } else {
    count++;
  }


  if(count == 4){
    flag = 0;
  }

  return flag;
  }
  return 0;
}