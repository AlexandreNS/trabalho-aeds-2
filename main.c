#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/base.c" // contem structs e funcoes essenciais para a construção do jogo
#include "libs/roubaMontes.c" // funcoes principais do jogo rouba montes

int main(int argc, char const *argv[]){
  int num_baralhos, num_jogadores, num_jogadas = 0;
  Jogador *jogadores;
  Pilha *compra = criaPilha();
  Lista *descarte = criarLista();

  printf("Entre com a quantidade de jogadores: ");
  scanf("%d", &num_jogadores);
  setbuf(stdin, NULL);

  jogadores = (Jogador*)malloc(num_jogadores*sizeof(Jogador));
  for (int i = 0; i < num_jogadores; i++) {
    printf("Nome do %d° jogador: ");
    fgets(jogadores[i].nome, 29, stdin);
    setbuf(stdin, NULL);
  }

  printf("Entre com o numero de baralhos: ");
  scanf("%d", &num_baralhos);
  setbuf(stdin, NULL);
  return 0;
}
