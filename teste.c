#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libs/base.c" // contem structs e funcoes essenciais para a construção do jogo
#include "libs/roubaMontes.c" // funcoes principais do jogo rouba montes

void teste_roubarMonte();
void teste_areaDescarte();
void testa_proprioMonte();

int main(int argc, char const *argv[]){
  srand(time(NULL));

  int num_jogadores = 3;
  int num_baralhos = 1;
  int num_jogadas = 0;
  char nomes[][30] = {"Alexandre", "Paulo", "Guilherme"};

  Pilha *compra = criaPilha();
  Lista *descarte = criarLista();
  Jogador *jogadores;
  jogadores = (Jogador*)malloc(num_jogadores*sizeof(Jogador));

  for (int i = 0; i < num_jogadores; i++) {
    strcpy(jogadores[i].nome, nomes[i]);
    jogadores[i].monte = criaPilha();
  }
  // // int num_baralhos, num_jogadores, num_jogadas = 0;
  // // Jogador *jogadores;
  // // Pilha *compra = criaPilha();
  // // Lista *descarte = criarLista();
  // //
  // // printf("Entre com a quantidade de jogadores: ");
  // // scanf("%d", &num_jogadores);
  // // setbuf(stdin, NULL);
  // //
  // // jogadores = (Jogador*)malloc(num_jogadores*sizeof(Jogador));
  // // for (int i = 0; i < num_jogadores; i++) {
  // //   printf("Nome do %d° jogador: ", i+1);
  // //   fgets(jogadores[i].nome, 29, stdin);
  // //   setbuf(stdin, NULL);
  // //
  // //   jogadores[i].monte = criaPilha();
  // // }
  // //
  // // printf("Entre com o numero de baralhos: ");
  // // scanf("%d", &num_baralhos);
  // // setbuf(stdin, NULL);
  //
  embaralha(num_baralhos, compra);
  printJogador(jogadores, num_jogadores);
  Carta carta_atual;
  int continua_jogada = 0;

  desempilha(compra, &carta_atual);
  while ( pilhaVazia(compra) == 0 ) {
    continua_jogada = direciona_carta(carta_atual, jogadores, num_jogadores, descarte, num_jogadas);
    if( continua_jogada == 0 ) num_jogadas++;
    desempilha(compra, &carta_atual);
  }
  printJogador(jogadores, num_jogadores);

  printf("\n\n\n\n\n");

  ganhadores(jogadores, num_jogadores);
  return 0;
}
void teste_areaDescarte(){
  Carta carta;

  int jogador_vez = 0;
  int num_jogadores = 3;
  char nomes[][30] = {"Alexandre", "Paulo", "Guilherme"};
  Lista *descarte = criarLista();
  Jogador *jogadores;
  jogadores = (Jogador*)malloc(num_jogadores*sizeof(Jogador));
  for (int i = 0; i < num_jogadores; i++) {
    strcpy(jogadores[i].nome, nomes[i]);
    jogadores[i].monte = criaPilha();
  }
////////////////////////////////////////////////////////////////////////////////
  carta.naipe = COPAS; carta.numero = DAMA;
  insere_ultimoLista(descarte, carta);

  carta.naipe = ESPADAS; carta.numero = AS;
  insere_ultimoLista(descarte, carta);

  carta.naipe = PAUS; carta.numero = QUATRO;
  insere_ultimoLista(descarte, carta);

  carta.naipe = OUROS; carta.numero = VALETE;
  insere_ultimoLista(descarte, carta);
////////////////////////////////////////////////////////////////////////////////
  carta.naipe = OUROS; carta.numero = SETE;
  empilha(jogadores[0].monte, carta);

  printf("Area de Descarte:\n");
  printLista(descarte);
  printf("\n");

  printJogador(jogadores, num_jogadores);
////////////////////////////////////////////////////////////////////////////////
  printf("\n");
  carta.naipe = PAUS; carta.numero = SETE;
  printf("%d\n", areaDescarte(jogadores, jogador_vez, carta, descarte));
  printf("\n");
////////////////////////////////////////////////////////////////////////////////

  printJogador(jogadores, num_jogadores);
}

void testa_proprioMonte(){
  Carta carta;

  int jogador_vez = 0;
  int num_jogadores = 3;
  char nomes[][30] = {"Alexandre", "Paulo", "Guilherme"};
  Jogador *jogadores;
  jogadores = (Jogador*)malloc(num_jogadores*sizeof(Jogador));
  for (int i = 0; i < num_jogadores; i++) {
    strcpy(jogadores[i].nome, nomes[i]);
    jogadores[i].monte = criaPilha();
  }
  carta.naipe = PAUS; carta.numero = SETE;
  empilha(jogadores[0].monte, carta);

  carta.naipe = OUROS; carta.numero = NOVE;
  empilha(jogadores[0].monte, carta);

  carta.naipe = ESPADAS; carta.numero = QUATRO;
  empilha(jogadores[0].monte, carta);

  printJogador(jogadores, num_jogadores);
////////////////////////////////////////////////////////////////////////////////
  printf("\n");
  carta.naipe = PAUS; carta.numero = TRES;
  printf("%d\n", proprioMonte(jogadores[jogador_vez], carta));
  printf("\n");
////////////////////////////////////////////////////////////////////////////////

  printJogador(jogadores, num_jogadores);
}

void teste_roubarMonte(){
  Carta carta;
  carta.naipe = COPAS;
  carta.numero = VALETE;

  int jogador_vez = 1;
  int num_jogadores = 3;
  char nomes[][30] = {"Alexandre", "Paulo", "Guilherme"};
  Jogador *jogadores;
  jogadores = (Jogador*)malloc(num_jogadores*sizeof(Jogador));
  for (int i = 0; i < num_jogadores; i++) {
    strcpy(jogadores[i].nome, nomes[i]);
    jogadores[i].monte = criaPilha();
  }
  empilha(jogadores[0].monte, carta);
  carta.naipe = COPAS;
  carta.numero = AS;
  empilha(jogadores[0].monte, carta);
  printJogador(jogadores, num_jogadores);
  int is_roubar = boolRoubarMonte(jogadores, num_jogadores, carta, jogador_vez);

  printf("\n");
  printf("%d\n", is_roubar);
  printf("\n");

  roubarMonte(jogadores, is_roubar-1, jogador_vez, carta);
  printJogador(jogadores, num_jogadores);
}
