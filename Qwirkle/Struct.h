typedef struct{
  char letra;
  char numero;
}peca;

typedef struct{
  char nome[20];
  int qpecas;
  peca pecas[6];
  int pontos;
}dados;