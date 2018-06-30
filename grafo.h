#ifndef _GRAFO_H
#define _GRAFO_H

#include <string.h>
#include <graphviz/cgraph.h>
#include "lista.h"

static const int TEST = 0;
static const int SIMPLIFICADO = 0;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo tem um nome, que é uma "string"

typedef struct grafo *grafo;
typedef struct vertice *vertice;
typedef struct aresta *aresta;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo pode ser direcionado ou não
// 
// o grafo tem um nome, que é uma "string"

struct grafo {
  char* nome;
  long dir;
  lista vert;
  long v;
  long a;
};

//------------------------------------------------------------------------------
// vertice com rotulo=subconjunto de {1, ..., n}, nome, vizinhos e grau

struct vertice {
	char* nome;
	char* rotulo;
	const char* cor;
	lista vizinhos;	
	long grau;
};

//------------------------------------------------------------------------------
// aresta com os dois vertices e um peso=recomendações

struct aresta {
	vertice vert;
	long peso;
};

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g);

//------------------------------------------------------------------------------
// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes

noh imprimeVert(noh aux,int ares);

//------------------------------------------------------------------------------
// imprime as arestas com seus parâmetros e informações relevantes
// usado para testes

noh imprimeAres(noh aux, vertice nome);

//------------------------------------------------------------------------------
// cria um novo grafo alocando memória e definindo suas variáveis

grafo criaGrafo(char *nome, long dir, long vert, long ares);

//------------------------------------------------------------------------------
// cria um novo vertice alocando memória e definindo suas variáveis

vertice criaVert(char *nome, long grau);

//------------------------------------------------------------------------------
// cria uma nova aresta alocando memória e definindo suas variáveis

aresta criaAres(vertice v, long peso);

//------------------------------------------------------------------------------
// insere os vertices ao grafo

void insereVert(Agraph_t *g, grafo gr);

//------------------------------------------------------------------------------
// constrói a vizinhança dos vertices

void constroiViz(Agraph_t *g, grafo gr);

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna o vertice ou NULL se nao encontrar

vertice procuraVert(lista l, char *p);

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna a aresta ou NULL se nao encontrar

aresta procuraAres(noh aux, vertice v);

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroiGrafo(grafo g);

//------------------------------------------------------------------------------
// devolve o vértice de nome 'nome' em g

vertice verticeDeNome(char *nome, grafo g);

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input
// 
// devolve o grafo lido,
//         ou 
//         NULL, em caso de erro 

grafo leGrafo(FILE *input);  

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// cada vértice do grafo escrito tem um atributo de nome "color" e o
// valor desse atributo deve ser uma cor especificada no formato
// "#rrggbb" onde rr, gg e bb são números de dois dígitos em
// representação hexadecimal indicando as intensidades de vermelho
// (red), verde (green) e azul (blue) em que se decompõe essa cor
//
// o valor deste atributo para o vértice v deve ser uma função do
// valor de cor(v,g)
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 

grafo escreveGrafo(grafo g);

//------------------------------------------------------------------------------
// busca vertice pelo nome no grafo e devolve sua cor

const char *cor(char *vertNome, grafo g);

//------------------------------------------------------------------------------
// preenche o vetor v (presumidamente um vetor com n_vertices(g)
// posições) com os vértices de g ordenados de acordo com uma busca em
// largura lexicográfica sobre g a partir de r e devolve v

char **buscaLexicografica(grafo g, char **v);

//------------------------------------------------------------------------------
// imprime conjunto de vertices

void imprimeConjunto(lista conjuntoVertices);

//------------------------------------------------------------------------------
// busca maior rotulo entre todos os vertices do conjunto usando strcmp()

vertice buscaMaiorRotulo(lista conjuntoVertices);

//------------------------------------------------------------------------------
// concatena um numero ao rotulo do vertice

void adicionaRotulo(char *rotulo, long l);

//------------------------------------------------------------------------------
// caminha pelo grafo e zera os rótulos de todos os vertices

void zeraRotulos(grafo g);

//------------------------------------------------------------------------------
// colore os vértices de g de maneira "gulosa" segundo a ordem dos
// vértices em v e devolve o número de cores utilizado
//
// ao final da execução,
//     1. cor(v,g) > 0 para todo vértice de g
//     2. cor(u,g) != cor(v,g), para toda aresta {u,v} de g

int colore(grafo g, char **v);

//------------------------------------------------------------------------------
// garante que sera escolhida uma cor que nao é utilizada pelos vizinhos do
// vertice de maneira recursiva, cada nova tentativa escolhe uma cor do
// vetor de cores hexadecimais HEX definido logo abaixo

const char *garanteCor(vertice vert, const char *novaCor, int tentativa);

//------------------------------------------------------------------------------
#endif
