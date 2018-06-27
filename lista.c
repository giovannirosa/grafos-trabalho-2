#include "lista.h"

// inicia lista alocando memória e iniciando parâmetros
lista iniciaLista(void) {
  lista l = malloc(sizeof(struct lista));

  l->tam = 0;
  l->ini = NULL;
  l->fim = NULL;

  return l;
}

// libera lista da memória, um nó de cada vez, então a lista
void liberaLista(lista l) { 
  noh aux;
  while((aux = l->fim)) {
    l->fim = aux->ant;
    free(aux);
  }
  free(l);
}

// cria noh para inserir na lista
noh criaNoh(void *cont) {
  noh aux = malloc(sizeof(struct noh));
  aux->cont = cont;
  aux->ant = NULL;
  aux->prox = NULL;

  return aux;
}

// insere nó com conteúdo passado no final da lista
noh insereLista(lista l, void *cont) {
  noh n = criaNoh(cont);

  if (l->tam == 0) {
    l->ini = n;
    l->fim = n;
  } else {
    l->fim->prox = n;
    n->ant = l->fim;
    l->fim = n;
  }
  l->tam++;

  return n;
}

// remove nó do final da lista
void removeLista(lista l) {
  noh aux = l->fim;
  if (!aux)
    return;

  noh ant = aux->ant;
  if (ant) {
    l->fim = ant;
    ant->prox = NULL;
  } else {
    l->ini = NULL;
    l->fim = NULL;
  }

  l->tam--;
  free(aux);
}

// remove nó específico da lista
void removeListaEspec(lista l, noh aux) {
  if (!aux)
    return;

  if (aux == l->ini && aux == l->fim) {
    l->ini = NULL;
    l->fim = NULL;
  } else if (aux == l->ini) {
    aux->prox->ant = NULL;
    l->ini = aux->prox;
  } else if (aux == l->fim) {
    aux->ant->prox = NULL;
    l->fim = aux->ant;
  } else {
    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
  }

  l->tam--;
  free(aux);
}

// copia o conteudo de uma lista
lista copiaLista(lista l) {
  lista copia = iniciaLista();
  for (noh aux = l->ini; aux != NULL; aux = aux->prox)
    insereLista(copia,aux->cont);
  return copia;
}