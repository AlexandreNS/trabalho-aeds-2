// variarveis para manipular o baralho
enum numero_carta{AS=1, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ, VALETE, DAMA, REI};
enum naipe_carta{PAUS=1, OUROS, COPAS, ESPADAS};

char NUMERO_CARTAS[][15] = {"AS", "DOIS", "TRES", "QUATRO",
"CINCO", "SEIS", "SETE", "OITO", "NOVE", "DEZ", "VALETE", "DAMA", "REI"};
char NAIPE_CARTAS[][15] = {"PAUS", "OUROS", "COPAS", "ESPADAS"};

// todas as structs do jogo
typedef struct CartaTag Carta;
typedef struct JogadorTag Jogador;
typedef struct ElementoTag Elemento;
typedef struct PilhaTag Pilha;
typedef struct ListaTag Lista;

// funcoes de manipulação de pilha
Pilha* criaPilha();
void liberaPilha(Pilha*);
int empilha(Pilha*, Carta);
int desempilha(Pilha*, Carta*);
int pilhaVazia(Pilha*);
void printPilha(Pilha*);

// funcoes de manipulação de lista
Lista* criarLista();
void limparLista(Lista*);
void excluirLista(Lista*);
int insere_ultimoLista(Lista*, Carta);
int insere_posicaoLista(Lista*, int, Carta);
int insere_ordenadoLista(Lista* l, Carta c);
int remove_ultimoLista(Lista*, Carta*);
int remove_posicaoLista(Lista*, int, Carta*);
int recupera_chaveLista(Lista*, Carta);
int recupera_posicaoLista(Lista*, int, Carta*);
int countLista(Lista*);
int listaVazia(Lista*);
void printLista(Lista*);

// funcoes com utilidade adicional
void formataString(char texto[]);
void printCarta(int id, int numero, int naipe);
void sprintCarta(int id, int numero, int naipe, char texto[]);

//------------------------------------------------------------------------------

typedef struct CartaTag{
  int naipe;
  int numero;
}Carta;

typedef struct JogadorTag{
  char nome[30];
  Pilha *monte;
}Jogador;

typedef struct ElementoTag{
  Carta valor;
  Elemento* proximo;
} Elemento;

typedef struct PilhaTag{
  Elemento *topo;
} Pilha;

typedef struct ListaTag{
  Elemento *inicio;
}Lista;

//////////////////////////////////////////////////////////////////////////////////////////////////////
Pilha* criaPilha(){
  Pilha* p;
  p = (Pilha*)malloc(sizeof(Pilha));
  p->topo = NULL;
  return p;
}
void liberaPilha(Pilha* p){
  while(p->topo != NULL){
    Elemento* aux;
    aux = p->topo;
    p->topo = aux->proximo;
    free(aux);
  }
}
int empilha(Pilha* p, Carta v){
  Elemento* e;
  e = (Elemento*)malloc(sizeof(Elemento));
  e->valor = v;
  e->proximo = p->topo;
  p->topo = e;
  return 1;
}
int desempilha(Pilha* p, Carta* v){
  if(pilhaVazia(p)) return 0;
  else{
    Elemento* aux;
    aux = p->topo;

    *v = aux->valor;
    p->topo = aux->proximo;

    free(aux);
    return 1;
  }
}
int pilhaVazia(Pilha* p){
  if(p->topo == NULL) return 1;
  else return 0;
}
int countPilha(Pilha* p){
  Elemento* aux = p->topo;
  int count = 0;
  while(aux != NULL){
    aux = aux->proximo;
    count++;
  }
  return count;
}
void printPilha(Pilha* p){
  if(pilhaVazia(p)) printf("A lista está Vazia!!!\n");
  else {
    Elemento* aux = p->topo;
    for (int i = 0; aux != NULL; i++) {
      printCarta(i+1, aux->valor.numero, aux->valor.naipe);
      aux = aux->proximo;
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
Lista* criarLista(){
  Lista* l = (Lista*)malloc(sizeof(Lista));
  l->inicio = NULL;
  return l;
}
void limparLista(Lista* l){
  Elemento* aux_prox = l->inicio;
  Elemento* aux_ant;
  while(aux_prox != NULL){
    aux_ant = aux_prox;
    aux_prox = aux_prox->proximo;
    free(aux_ant);
  }
  l->inicio = NULL;
}
void excluirLista(Lista* l){
  limparLista(l);
  free(l);
}
int insere_ultimoLista(Lista* l, Carta v){
  Elemento* e = (Elemento*)malloc(sizeof(Elemento));
  e->proximo = NULL;
  e->valor = v;
  if(listaVazia(l)) l->inicio = e;
  else{
    Elemento* aux;
    aux = l->inicio;
    while(aux->proximo != NULL) aux = aux->proximo;
    aux->proximo = e;
  }
  return 1;
}
int insere_posicaoLista(Lista* l, int p, Carta v){
  Elemento* e = (Elemento*)malloc(sizeof(Elemento));
  e->valor = v;
  e->proximo = NULL;

  if(p < 1 || p > countLista(l)+1) return 0;
  else if(listaVazia(l)) l->inicio = e;
  else if(p == 1){
    e->proximo = l->inicio;
    l->inicio = e;
  }else{
    Elemento* aux = l->inicio;
    int count = 1;
    while(aux != NULL && count+1 < p){
      aux = aux->proximo;
      count++;
    }
    e->proximo = aux->proximo;
    aux->proximo = e;
  }
  return 1;
}
int insere_ordenadoLista(Lista* l, Carta c){
  Elemento* aux = l->inicio;
  int p = 1;
  while(aux != NULL){
    if(c.numero <= aux->valor.numero) break;
    else p++;
    aux = aux->proximo;
  }
  insere_posicaoLista(l, p, c);
  return 0;
}
int remove_ultimoLista(Lista* l, Carta* v){
  if(listaVazia(l)) return 0;
  else{
    Elemento* aux = l->inicio;
    if(aux->proximo == NULL){
      *v = aux->valor;
      free(aux);
      l->inicio = NULL;
    }else{
      while (aux->proximo->proximo != NULL) {
        aux = aux->proximo;
      }
      *v = aux->proximo->valor;
      free(aux->proximo);
      aux->proximo = NULL;
    }
    return 1;
  }
}
int remove_posicaoLista(Lista* l, int p, Carta* v){
  Elemento *aux = l->inicio;

  if(p < 1 || p > countLista(l)) return 0;
  else if(p == 1){
    *v = aux->valor;
    l->inicio = l->inicio->proximo;
    free(aux);
  }else{
    int count = 1;
    while (aux->proximo != NULL && count+1 < p) {
      aux = aux->proximo;
      count++;
    }
    Elemento *aux2 = aux->proximo;
    *v = aux2->valor;
    aux->proximo = aux->proximo->proximo;
    free(aux2);
  }
}
int recupera_chaveLista(Lista* l, Carta v){
  Elemento *aux = l->inicio;
  int count = 1, retorno = 0;

  while(aux != NULL){
    if(aux->valor.numero == v.numero){
      retorno = count;
      break;
    }else{
      aux = aux->proximo;
      count++;
    }
  }
  return retorno;
}
int recupera_posicaoLista(Lista* l, int p, Carta *v){
  Elemento *aux = l->inicio;
  int count = 1;

  while(aux != NULL){
    if(count == p){
      *v = aux->valor;
      return 1;
      break;
    }else{
      aux = aux->proximo;
      count++;
    }
  }
  return 0;
}
int countLista(Lista* l){
  Elemento* aux = l->inicio;
  int count = 0;
  while(aux != NULL){
    aux = aux->proximo;
    count++;
  }
  return count;
}
int listaVazia(Lista* l){
  if(l->inicio == NULL) return 1;
  else return 0;
}
void printLista(Lista* l){
  if(listaVazia(l)) printf("A lista está Vazia!!!\n");
  else {
    Elemento* aux = l->inicio;
    for (int i = 0; aux != NULL; i++) {
      printCarta(i+1, aux->valor.numero, aux->valor.naipe);
      aux = aux->proximo;
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void formataString(char texto[]){
  int len = strlen(texto);
  if(texto[len-1] == '\n') texto[len-1] = 0;
}
void printCarta(int id, int numero, int naipe){
  printf("%d° Carta: %s - %s\n", id, NUMERO_CARTAS[numero-1], NAIPE_CARTAS[naipe-1]);
}
void sprintCarta(int id, int numero, int naipe, char texto[]){
  sprintf(texto, "- %s - %s\n", NUMERO_CARTAS[numero-1], NAIPE_CARTAS[naipe-1]);
}
