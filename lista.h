#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// declara nó da lista
typedef struct noh *noh;
// nó da lista com conteudo, proximo e anterior
struct noh {
	void *cont;
	noh prox, ant;
};

// declara lista
typedef struct lista *lista;
// lista com inicio, fim e tamanho
struct lista {
	noh ini, fim;
	long tam;
};

// inicia lista alocando memória e iniciando parâmetros
lista iniciaLista(void);

// libera lista da memória, um nó de cada vez, então a lista
void liberaLista(lista l);

// cria noh para inserir na lista
noh criaNoh(void *cont);

// insere nó com conteúdo passado no final da lista
noh insereLista(lista l, void *cont);

// remove nó do final da lista
void removeLista(lista l);

// remove nó específico da lista
void removeListaEspec(lista l, noh aux);

// copia o conteudo de uma lista
lista copiaLista(lista l);

#endif