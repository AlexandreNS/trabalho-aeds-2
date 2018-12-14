#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libs/base.c" // contem structs e funcoes essenciais para a construção do jogo
#include "libs/roubaMontes.c" // funcoes principais do jogo rouba montes

int main(int argc, char const *argv[]){
  srand(time(NULL)); // setar tempo para embaralhar baralho

  // variarveis globais do Rouba Montes
  int num_baralhos, num_jogadores, num_jogadas = 0;
  Jogador *jogadores;
  Pilha *compra = criaPilha();
  Lista *descarte = criarLista();

  //entra com numero de jogadores
  printf("Entre com a quantidade de jogadores: ");
  scanf("%d", &num_jogadores);
  setbuf(stdin, NULL);

  //Preenche dados do Jogador
  jogadores = (Jogador*)malloc(num_jogadores*sizeof(Jogador));
  for (int i = 0; i < num_jogadores; i++) {
    printf("Nome do %d° jogador: ", i+1);
    fgets(jogadores[i].nome, 29, stdin);
    formataString(jogadores[i].nome);
    setbuf(stdin, NULL);

    jogadores[i].monte = criaPilha();
  }


  //entra com numero de baralhos usados
  printf("Entre com o numero de baralhos: ");
  scanf("%d", &num_baralhos);
  setbuf(stdin, NULL);
  // embaralha os baralhos
  embaralha(num_baralhos, compra);

  registraInicio(jogadores, num_jogadores, compra);

  // inicia a Partida de Rouba Montes
  Carta carta_atual;
  int continua_jogada = 0;
  desempilha(compra, &carta_atual);
  while ( pilhaVazia(compra) == 0 ) {
    continua_jogada = direciona_carta(carta_atual, jogadores, num_jogadores, descarte, num_jogadas);
    if( continua_jogada == 0 ) num_jogadas++;
    desempilha(compra, &carta_atual);
  }

  registraFinal(jogadores, num_jogadores, descarte);
  
  // Mostra ganhadores na tela
  printf("\n");
  ganhadores(jogadores, num_jogadores);
  return 0;
}
