#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"
#include "Tabuleiro.h"
#include "MoviValido.h"
#include <time.h>

//da dicas de como jogar ao usuario
void Instrucoes(){
  system("clr||clear");
  printf("Como usar esse programa:\n");
  printf("Para jogar uma peca digite 'jogar [peca] [x] [y]'\n");
  printf("Para trocar uma peca digite 'trocar [peca1] [peca2]...'\n");
  printf("Para passar a vez digite 'passar'\n");
  printf("Lembre-se que a letra de cada peca tem que ser maiuscula\n");
  printf("Aperte enter para continuar...");
  getchar();
  system("clr||clear");
}

//contabiliza os pontos acumulados com cada linha ou coluna preenchida
int AuxPontuacao(peca **Tabuleiro,int x,int auxX,int y,int auxY,int *Ptemp){

  //inicia o contador
  int count = 0;

  //inicia as verificacoes
  if(Tabuleiro[x+auxX][y+auxY].letra >= 'A' && Tabuleiro[x+auxX][y+auxY].letra <= 'Z'){

    //inicia as coordenadas
    int i = 0;
    int j = 0;

    //mantem as verificacoes ate nao haver mais elementos naquela linha ou coluna
    while(Tabuleiro[x+i][y+j].letra >= 'A' && Tabuleiro[x+i][y].letra <= 'Z'){

      //a cada elemento em sequencia, soma a pontuacao
      count++;

      //de acordo com as coordenadas fornecidas (que indicam lados, cima e baixo) acontece a incrementacao
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

    //soma a bonificacao de seis elementos
    if(count == 6){
      count += 6;
    }

    //incrementa a pontuacao temporaria
    *Ptemp += count;
  } 
  else {
    return 1;
  }
  return 0;
}

//soma os pontos acumulados
void Pontuacao(peca **Tabuleiro,int x, int y,int *Ptemp){

  //inicia a pontuacao temporaria e o contador
  *Ptemp = 0;
  int count = 0;

  //incrementa o contador
  count += AuxPontuacao(Tabuleiro,x,1,y,0,Ptemp);
  count += AuxPontuacao(Tabuleiro,x,-1,y,0,Ptemp);
  count += AuxPontuacao(Tabuleiro,x,0,y,1,Ptemp);
  count += AuxPontuacao(Tabuleiro,x,0,y,-1,Ptemp);

  //se a soma dos pontos for quatro, eh o primeiro elemento
  //entao a pontuacao eh 1
  if(count == 4){
    *Ptemp = *Ptemp + 1;
  }
}

//sorteia as pecas
void SortearPecas(dados *Jogador,int r,peca **PecasRestantes,int *qPecasRestantes){

  //define as condicoes de o jogador ter menos que seis pecas e existirem pecas restantes
  while(Jogador[r].qpecas < 6 && *qPecasRestantes != 0){

    //sorteia novas pecas
    char aux1 = 'A' + rand()%6;
    char aux2 = '1' + rand()%6;

    //retira as pecas sorteadas do ponteiro de pecas restantes
    int flag = 0;
    for(int i = 0;i<18;i++){
      for(int j = 0;j<6;j++){
        if(PecasRestantes[i][j].letra == aux1 && PecasRestantes[i][j].numero == aux2){
          PecasRestantes[i][j].letra = '0';
          PecasRestantes[i][j].numero = '0';
          *qPecasRestantes = *qPecasRestantes - 1;
          Jogador[r].pecas[Jogador[r].qpecas].letra = aux1;
          Jogador[r].pecas[Jogador[r].qpecas].numero = aux2;
          Jogador[r].qpecas = Jogador[r].qpecas + 1;
          flag = 1;
          break;
        }
      }
      if(flag == 1){
        break;
      }
    }
  }
  if(*qPecasRestantes == 0){
    printf("Nao ha mais pecas para sortear!\n");
  }
}

//inicializa o ponteiro de pecas do jogo
void InicializarPecasRestantes(peca **PecasRestantes){
  for(int i = 0;i<6;i++){
    for(int k = 0;k<3;k++){
      for(int j = 0;j<6;j++){
        PecasRestantes[j+(6*k)][i].letra = 'A'+ j;
        PecasRestantes[j+(6*k)][i].numero = '1'+i;
      }
    }
  }
}

//troca as pecas do jogador
int TrocarPeca(dados *Jogador,int r,peca **PecasRestantes,int *qPecasRestantes,char jogada[30]){

  int num = 0;
  int flag = 0;
  int PecaTrocada[6];

  if(jogada[7]<'A' || jogada[7]> 'F'){
    return 1;
  }
  do{

    //le as pecas a serem trocadas
    setbuf(stdin,NULL);
    char pecas[6][3];
    int p = 0;
    int a = 0;
    while(a==0){

      setbuf(stdin,NULL);
      pecas[p][0] = jogada[7+3*p];
      pecas[p][1] = jogada[8+3*p];
      pecas[p][2] = '\0';

      //para de ler ao encontrar o \n
      if(jogada[9+3*p] == '\n'){a=1;}
      p++;
      
    }

    

    //procura as pecas lidas nas pecas do jogador
    for(int j = 0; j<p ; j++){
      if(pecas[j][0] >= 'A' && pecas[j][0] <= 'F' && pecas[j][1] >= '1' && pecas[j][1] <= '6'){
        for(int i = 0;i<Jogador[r].qpecas;i++){
          if(pecas[j][0] == Jogador[r].pecas[i].letra && pecas[j][1] == Jogador[r].pecas[i].numero){

            //quando encontra, armazena
            flag = 1;
            PecaTrocada[j] = i;
            num++;
            break;

          }
        }

        //trata erros
        if(flag == 0){
          printf("Voce nao possui uma dessas pecas,tente de novo!\n");
          return 1;
        }
      } else {
        printf("ao menos uma das pecas eh invalidas, tente de novo!\n");
        return 1;
      }
    }
  }while(flag != 1);

  //devolve as pecas retiradas ao ponteiro de pecas restantes
  flag = 0;
  for(int i = 0;i<18;i++){
      for(int j = 0;j<6;j++){
        for(int k = 0 ; k<num; k++){
          if(PecasRestantes[i][j].letra == '0' && PecasRestantes[i][j].numero == '0'){
            PecasRestantes[i][j].letra = Jogador[r].pecas[PecaTrocada[k]].letra;
            PecasRestantes[i][j].numero = Jogador[r].pecas[PecaTrocada[k]].numero;
            flag = 1;
            break;
          }
        }
      }
      if(flag == 1){
        break;
      }
    }

  //sorteia novas pecas e apresenta na ordem
  for(int j = 0; j<num; j++){
    for(int i = PecaTrocada[j]-j;i<Jogador[r].qpecas-1;i++){
      Jogador[r].pecas[i] = Jogador[r].pecas[i+1];
    }
    Jogador[r].qpecas = Jogador[r].qpecas - 1;
  }
  printf("==========\nPecas trocadas com sucesso!\n==========\n");
  SortearPecas(Jogador,r,PecasRestantes,qPecasRestantes);
  return 0;
  
}

//funcao principal das jogadas
peca **Jogada(dados *Jogador,int r,peca **Tabuleiro,int *tam,int Largura[2],int Altura[2],int cheat,int possibilidades[4],int *Ptemp,char jogada[20]){

  //le a peca jogada
  int flag = 0;
  int PecaJogada;
  char peca[3] = {jogada[6],jogada[7],'\0'};

  //verifica que os caracteres sao validos
  if(peca[0] >= 'A' && peca[0] <= 'F' && peca[1] >= '1' && peca[1] <= '6'){

    //verifica se a peca faz parte da colecao do jogador
    for(int i = 0;i<Jogador[r].qpecas;i++){
      if(peca[0] == Jogador[r].pecas[i].letra && peca[1] == Jogador[r].pecas[i].numero){
        flag = 1;
        PecaJogada = i;
        break;
      }
    }

    //permite passagem da peca no modo cheat
    if(cheat == 1){
      Jogador[r].pecas[5].letra = peca[0];
      Jogador[r].pecas[5].numero = peca[1];
      PecaJogada = 5;
      flag = 1;
    }

    //trata erros
    if(flag == 0){
      printf("Voce nao possui essa peca,tente outra!\n");
      return Tabuleiro;
    }
  } 
  else {
    printf("Peca invalida, tente outra!\n");
    return Tabuleiro;
  }

  //converte coordenadas em char para int e adapta negativos
  int x,y;
  int aux = 0;
  if(jogada[9] == '-'){
    x = (jogada[10]-48)*-1;
    aux++;
  } else {
    x = jogada[9]-48;
  }
  if(jogada[11+aux] == '-'){
    y = (jogada[12+aux]-48)*-1;
  } else {
    y = (jogada[11+aux]-48);
  }

  //verifica a necessidade de aumentar o tabuleiro
  if(Altura[1] >= (*tam/2)-1 ||Altura[0] <= -1*((*tam/2)-1) || Largura[1] >= (*tam/2)-1 ||Largura[0] <= -1*((*tam/2)-1)){
    //aumenta o tabuleiro e atualiza as possibilidades
    Tabuleiro = AtualizarTabuleiro(Tabuleiro,tam,(*tam+10));
    possibilidades[0] = possibilidades[0] + 5;
    possibilidades[1] = possibilidades[1] + 5;
    possibilidades[2] = possibilidades[2] + 5;
    possibilidades[3] = possibilidades[3] + 5;
    *tam = *tam + 10;
  }

  //verifica a validade do movimento
  if(MovimentoValido(Tabuleiro,Jogador[r].pecas[PecaJogada],x+(*tam/2),y+(*tam/2),0,tam,possibilidades) == 1){
    
    //aumenta a visualizacao do tabuleiro se necessario
    if(y <= Largura[0]){
      Largura[0] = y-1;
    }
    if(y >= Largura[1]){
      Largura[1] = y+1;
    }
    if(x <= Altura[0]){
      Altura[0] = x-1;
    }
    if(x >= Altura[1]){
      Altura[1] = x+1;
    }

    //aloca a peca na posicao correta
    Tabuleiro[x+(*tam/2)][y+(*tam/2)].letra = Jogador[r].pecas[PecaJogada].letra;
    Tabuleiro[x+(*tam/2)][y+(*tam/2)].numero = Jogador[r].pecas[PecaJogada].numero;

    //retira a peca da colecao do jogador
    for(int i = PecaJogada;i<Jogador[r].qpecas-1;i++){
      Jogador[r].pecas[i] = Jogador[r].pecas[i+1];
    }

    //diminui a quantidade de pecas no modo chear
    if(cheat == 0){
      Jogador[r].qpecas = Jogador[r].qpecas - 1;
    }

    //apresenta pontuacao e mensagens
    Pontuacao(Tabuleiro,x+(*tam/2),y+(*tam/2),Ptemp);
    printf("==========\nPeca jogada com sucesso!\n==========\n");
  } else {
    printf("=================\nMovimento invalido!\n=================\n");
  }
  return Tabuleiro;
}
