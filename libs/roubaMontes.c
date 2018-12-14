/*
  Funções que alteram comportamento do baralho durante o jogo
*/
// n -> numero de baralhos, c -> area de compra
void embaralha(int n, Pilha* c);
// c-> carta, j -> jogadores, d -> descarte, njs -> numero de jogadas
int direciona_carta(Carta c, Jogador* j, int nj, Lista* d, int njs);
int boolRoubarMonte(Jogador* j, int nj, Carta c, int jv);
void roubarMonte(Jogador* j, int id_j, int jv, Carta c);
int areaDescarte(Jogador* j, int jv, Carta c, Lista* d);
int proprioMonte(Jogador j, Carta c);
/*
  Funções que mostram dados sobre a partida
*/
void ganhadores(Jogador* j, int nj);
void print_ordena_monte(Jogador j, int n);
void printJogador(Jogador *j, int nj);
void registraJogada(char texto[]);
void registraInicio(Jogador* j, int nj, Pilha* c);
void registraFinal(Jogador* j, int nj, Lista* d);


// -----------------------------------------------------------------------------

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
  char nome_jogada[100];
  if(njs < nj){
    empilha(j[njs].monte, c);

    //Registro no arquivo dados.md
    sprintf(nome_jogada, "- **%s** colocou %s - %s no seu Monte\n",
    j[njs].nome, NUMERO_CARTAS[c.numero-1], NAIPE_CARTAS[c.naipe-1]);
    registraJogada(nome_jogada);
    //Registro no arquivo dados.md

    return 0;
  }
  int jv = njs%nj;
  int rouba = boolRoubarMonte(j, nj, c, jv);
  if ( rouba != 0 ) { /* roubar_monte ? */
    int id_j = rouba-1;
    roubarMonte(j, id_j, jv, c);

    //Registro no arquivo dados.md
    sprintf(nome_jogada, "- **%s** roubou monte do `%s` com %s - %s\n",
    j[jv].nome, j[id_j].nome, NUMERO_CARTAS[c.numero-1], NAIPE_CARTAS[c.naipe-1]);
    registraJogada(nome_jogada);
    //Registro no arquivo dados.md

    return 1;
  } else if(areaDescarte(j, jv, c, d) != 0){ /* pegar na area de descarte*/

    //Registro no arquivo dados.md
    sprintf(nome_jogada, "- **%s** pegou carta da área de descarte com %s - %s\n",
    j[jv].nome, NUMERO_CARTAS[c.numero-1], NAIPE_CARTAS[c.naipe-1]);
    registraJogada(nome_jogada);
    //Registro no arquivo dados.md

    return 1;
  }else if(proprioMonte(j[jv], c)){ /* no proprio monte*/

    //Registro no arquivo dados.md
    sprintf(nome_jogada, "- **%s** colocou %s - %s no proprio monte\n",
    j[jv].nome, NUMERO_CARTAS[c.numero-1], NAIPE_CARTAS[c.naipe-1]);
    registraJogada(nome_jogada);
    //Registro no arquivo dados.md

    return 1;
  }
  else {
    insere_posicaoLista(d, 1, c);

    //Registro no arquivo dados.md
    sprintf(nome_jogada, "- **%s** colocou %s - %s na área de descarte\n",
    j[jv].nome, NUMERO_CARTAS[c.numero-1], NAIPE_CARTAS[c.naipe-1]);
    registraJogada(nome_jogada);
    //Registro no arquivo dados.md

    return 0;
  }
  return 0;
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
  FILE *arq = fopen("info-jogo/dados.md", "a+");
  if (arq == NULL){
    printf("Erro >>> Arquivo não encontrado\n");
    exit(EXIT_FAILURE);
  }else{
    fprintf(arq, "%s", texto);
    if (ferror(arq)){
      fclose(arq);
      printf("Erro >>> Não foi possivel escrever no arquivo\n");
      exit(EXIT_FAILURE);
    }
    fclose(arq);
  }
}
void registraInicio(Jogador* j, int nj, Pilha* c){
  time_t atual;
  atual = time(NULL);
  struct tm tm = *localtime(&atual);
  char cabecalho[70];
  sprintf(cabecalho ,"### Dados da Partida de %d-%d-%d:\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

  FILE *arq = fopen("info-jogo/dados.md", "w+");
  if (arq == NULL){
    printf("Erro >>> Arquivo não encontrado\n");
    exit(EXIT_FAILURE);
  }else{
    fprintf(arq, "<img src=\"roubaMonte.jpg\" width=\"90px\" style=\"margin-right:30px\" align=\"right\" />\n", cabecalho);
    fprintf(arq, "%s#### Jogadores: \n", cabecalho);
    for (int i = 0; i < nj; i++) {
      fprintf(arq, "%d. `%s`\n", i+1, j[i].nome);
    }
    fprintf(arq, "\n");

    fprintf(arq, "#### Baralho: \n");

    Elemento* aux = c->topo;
    for (int i = 0; aux != NULL; i++) {
      sprintCarta(i+1, aux->valor.numero, aux->valor.naipe, cabecalho);
      fprintf(arq, "%s", cabecalho);
      aux = aux->proximo;
    }

    fprintf(arq, "\n#### Jogadas da Partida: \n");
    if (ferror(arq)){
      fclose(arq);
      printf("Erro >>> Não foi possivel escrever no arquivo\n");
      exit(EXIT_FAILURE);
    }
    fclose(arq);
  }
}
void registraFinal(Jogador* j, int nj, Lista* d){
  char cabecalho[70];
  FILE *arq = fopen("info-jogo/dados.md", "a+");
  if (arq == NULL){
    printf("Erro >>> Arquivo não encontrado\n");
    exit(EXIT_FAILURE);
  }else{
    fprintf(arq, "\n\n#### Final da Partida: \n");
    for (int i = 0; i < nj; i++) {
      fprintf(arq, "##### Monte do %s:\n", j[i].nome);

      Elemento* aux = j[i].monte->topo;
      if(aux == NULL) fprintf(arq, "Monte Vazio!!!\n\n");
      for (int i = 0; aux != NULL; i++) {
        sprintCarta(i+1, aux->valor.numero, aux->valor.naipe, cabecalho);
        fprintf(arq, "%s", cabecalho);
        aux = aux->proximo;
      }
      fprintf(arq, "\n");
    }
    fprintf(arq, "\n");

    fprintf(arq, "##### Área de Descarte: \n");

    Elemento* aux = d->inicio;
    for (int i = 0; aux != NULL; i++) {
      sprintCarta(i+1, aux->valor.numero, aux->valor.naipe, cabecalho);
      fprintf(arq, "%s", cabecalho);
      aux = aux->proximo;
    }

    if (ferror(arq)){
      fclose(arq);
      printf("Erro >>> Não foi possivel escrever no arquivo\n");
      exit(EXIT_FAILURE);
    }
    fclose(arq);
  }
}
