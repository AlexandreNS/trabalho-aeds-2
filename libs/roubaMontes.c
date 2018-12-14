void embaralha(int n, Pilha* c);
int direciona_carta(Carta c, Jogador* j, int nj, Lista* d, int njs);

void ganhadores(Jogador* j, int nj);
void print_ordena_monte(Jogador j, int n);
void printJogador(Jogador *j, int nj);
void registraJogada(char texto[]);
void registraInicio(Jogador* j, int nj, Pilha* c);

int boolRoubarMonte(Jogador* j, int nj, Carta c, int jv);
void roubarMonte(Jogador* j, int id_j, int jv, Carta c);

int areaDescarte(Jogador* j, int jv, Carta c, Lista* d);

int proprioMonte(Jogador j, Carta c);

void embaralha(int n, Pilha* c){
  Lista *baralho = criarLista();
  int num_cartas = n*52;
  int pos_l;
  Carta aux;
  for (int i = 1; i <= n; i++) {
    for (int j = PAUS; j <= ESPADAS; j++) {
      for (int k = AS; k <= REI; k++) {
        aux.naipe = j;
        aux.numero = k;
        insere_ultimoLista(baralho, aux);
      }
    }
  }
  while (num_cartas > 0) {
    pos_l = (rand()%num_cartas)+1;

    remove_posicaoLista(baralho, pos_l, &aux);
    empilha(c, aux);

    num_cartas--;
  }
}
int direciona_carta(Carta c, Jogador* j, int nj, Lista* d, int njs){
  if(njs < nj){
    empilha(j[njs].monte, c);
    return 0;
  }
  int jv = njs%nj;
  int rouba = boolRoubarMonte(j, nj, c, jv);
  if ( rouba != 0 ) { /* roubar_monte ? */
    int id_j = rouba-1;
    roubarMonte(j, id_j, jv, c);
    return 1;
  } else if(areaDescarte(j, jv, c, d) != 0) return 1;  /* pegar na area de descarte*/
  else if(proprioMonte(j[jv], c)) return 1; /* no proprio monte*/
  else {
    insere_posicaoLista(d, 1, c);
    return 0;
  }
  return 0;
}

void ganhadores(Jogador* j, int nj){
  int *ids_g = (int*)malloc(nj*sizeof(int));
  int maior = 0;
  for (int i = 0; i < nj; i++) {
    ids_g[i] = countPilha(j[i].monte);
    if(maior < ids_g[i]) maior = ids_g[i];
  }

  printf("\tGanhador(es) do Rouba Montes: \n");
  for (int i = 0; i < nj; i++) {
    if(ids_g[i] == maior){
      printf("Nome: %s\n", j[i].nome);
      printf("Lista de Cartas: \n\n");
      print_ordena_monte(j[i], ids_g[i]);
      printf("\n\n");
    }
  }
  free(ids_g);
}
void printJogador(Jogador *j, int nj){
  printf("Lista de Jogadores: \n");
  for (int i = 0; i < nj; i++) {
    printf("\t%s:\n", j[i].nome);
    printPilha(j[i].monte);
  }
}
void print_ordena_monte(Jogador j, int n){
  Lista *exibe_cartas = criarLista();
  Carta aux;
  for (int i = 0; i < n; i++) {
    desempilha(j.monte, &aux);
    insere_ordenadoLista(exibe_cartas, aux);
  }
  printLista(exibe_cartas);
  excluirLista(exibe_cartas);
}
void registraJogada(char texto[]){
  FILE *arq = fopen("dados.txt", "a+");
  if (arq == NULL){
    printf("Erro >>> Arquivo não encontrado\n");
    exit(EXIT_FAILURE);
  }else{
    fprintf(arq, texto);
    if (ferror(arq)){
      fclose(arq);
      printf("Erro >>> Não foi possivel escrever no arquivo\n");
      exit(EXIT_FAILURE);
    }
    fclose(arq);
  }
}
void registraInicio(Jogador* j, int nj, Pilha* c){
  FILE *arq = fopen("dados.txt", "a+");
  if (arq == NULL){
    printf("Erro >>> Arquivo não encontrado\n");
    exit(EXIT_FAILURE);
  }else{
    // fprintf(arq, texto, media);
    if (ferror(arq)){
      fclose(arq);
      printf("Erro >>> Não foi possivel escrever no arquivo\n");
      exit(EXIT_FAILURE);
    }
    fclose(arq);
  }
}

int boolRoubarMonte(Jogador* j, int nj, Carta c, int jv){
  for (int i = 1; i <= nj; i++) {
    if(i == jv+1 || pilhaVazia(j[i-1].monte)) continue;
    else if(j[i-1].monte->topo->valor.numero == c.numero){
      return i;
    }
  }
  return 0;
}
void roubarMonte(Jogador* j, int id_j, int jv, Carta c){
  empilha(j[id_j].monte, c);
  Elemento *aux = j[id_j].monte->topo;
  while (aux->proximo != NULL) aux = aux->proximo;
  aux->proximo = j[jv].monte->topo;
  j[jv].monte->topo = j[id_j].monte->topo;
  j[id_j].monte->topo = NULL;
}

int areaDescarte(Jogador* j, int jv, Carta c, Lista* d){
  int id_d = recupera_chaveLista(d, c);
  if(id_d != 0){
    Carta c_add;
    remove_posicaoLista(d, id_d, &c_add);
    empilha(j[jv].monte, c_add);
    empilha(j[jv].monte, c);
    return 1;
  }else return 0;
}

int proprioMonte(Jogador j, Carta c){
  if(pilhaVazia(j.monte)) return 0;
  if(j.monte->topo->valor.numero == c.numero){
    empilha(j.monte, c);
    return 1;
  }else return 0;
}
