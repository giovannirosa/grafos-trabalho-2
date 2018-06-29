#include "grafo.h"

//------------------------------------------------------------------------------
// MÉTODOS DE IMPRESSÃO - TESTE
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g) {
	if (TEST) printf("------------------------------------------\n");
  printf("strict graph %s {\n", g->nome);
	if (!SIMPLIFICADO) imprimeVert(g->vert->ini,0);
	imprimeVert(g->vert->ini,1);
	printf("}\n");
	if (TEST) printf("------------------------------------------\n");
}

//------------------------------------------------------------------------------
// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes

noh imprimeVert(noh aux, int ares) {
	if (!aux)
		return aux;
	vertice v = (vertice) aux->cont;
	if (!SIMPLIFICADO) {
		if (!ares) {
			printf("  %s [rotulo=%s]\n", v->nome, v->rotulo);
			// printf("  %s [rotulo=", v->nome);
			// for (noh aux2 = v->rotulo->ini; aux2 != NULL; aux2 = aux2->prox) {
			// 	int* r = (int*) aux2->cont;
			// 	printf("%d", *r);
			// 	if (aux2->prox != NULL)
			// 		printf(",");
			// }
			// printf("]\n");
		}
		if (ares)
			imprimeAres(v->vizinhos->ini,v);
	} else {
		printf("  %s", v->nome);
		if (ares)
			imprimeAres(v->vizinhos->ini,v);
		printf("\n");
	}
	return imprimeVert(aux->prox,ares);
}

//------------------------------------------------------------------------------
// imprime as arestas com seus parâmetros e informações relevantes
// usado para testes

noh imprimeAres(noh aux, vertice v) {
	if (!aux)
		return aux;
	aresta a = (aresta) aux->cont;
	if (!SIMPLIFICADO) {
		printf("  %s -- %s [label=%ld]\n", v->nome, a->vert->nome, a->peso);
	} else {
		printf("->%s[%ld]", a->vert->nome, a->peso);
	}
	return imprimeAres(aux->prox,v);
}

//------------------------------------------------------------------------------
// MÉTODOS DE CRIAÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// cria um novo grafo alocando memória e definindo suas variáveis

grafo criaGrafo(char *nome, long dir, long vert, long ares) {
  grafo gr = malloc(sizeof(struct grafo));
  gr->nome = nome;
	gr->dir = dir;	 
	gr->v = vert;
	gr->a = ares;
  gr->vert = iniciaLista();
  return gr;
}

//------------------------------------------------------------------------------
// cria um novo vertice alocando memória e definindo suas variáveis

vertice criaVert(char *nome, long grau) {
  vertice vert = malloc(sizeof(struct vertice));
  vert->nome = nome;
  vert->grau = grau;
  vert->rotulo = iniciaLista();
  vert->vizinhos = iniciaLista();
  return vert;
}

//------------------------------------------------------------------------------
// cria uma nova aresta alocando memória e definindo suas variáveis

aresta criaAres(vertice v, long peso) {
  aresta ares = malloc(sizeof(struct aresta));
  ares->vert = v;
  ares->peso = peso;
  return ares;
}

//------------------------------------------------------------------------------
// MÉTODOS DE INSERÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// insere os vertices ao grafo

void insereVert(Agraph_t *g, grafo gr) {
	if (TEST) printf("------------------------------------------\n");
  for(Agnode_t *v = agfstnode(g); v; v = agnxtnode(g,v)) {
      vertice vert = criaVert(agnameof(v),agcountuniqedges(g,v,1,1));
			if (TEST) printf("Aloca vertice: %s com grau: %ld\n", vert->nome, vert->grau);
			insereLista(gr->vert, vert);			
			if (TEST) printf("------------------------------------------\n");					
	}
}

//------------------------------------------------------------------------------
// constrói a vizinhança dos vertices

void constroiViz(Agraph_t *g, grafo gr) {
	for(Agnode_t *v = agfstnode(g); v; v = agnxtnode(g,v)) {
		if (TEST) printf("------------------------------------------\n");
		if (TEST) printf("Construindo vizinhança do %s\n", agnameof(v));
		for (Agedge_t *a = agfstout(g, v); a; a = agnxtout(g, a)) {
			Agnode_t *tail = NULL;
			Agnode_t *head = NULL;

			tail = agtail(a);
			head = aghead(a);
			// printf("Tail: %s Head: %s\n", agnameof(tail), agnameof(head));

			vertice auxTail = procuraVert(gr->vert,agnameof(tail));
			vertice auxHead = procuraVert(gr->vert,agnameof(head));

			// printf("Achou tail: %s Achou head: %s\n", auxTail->nome, auxHead->nome);

			aresta ares = criaAres(auxHead,1);
			insereLista(auxTail->vizinhos, ares);
			if (TEST) printf("Inseriu aresta: %s -> %s\n", auxTail->nome, ares->vert->nome);

			ares = criaAres(auxTail,1);
			insereLista(auxHead->vizinhos, ares);
			if (TEST) printf("Inseriu aresta: %s -> %s\n", auxHead->nome, ares->vert->nome);
		}
	}
}

//------------------------------------------------------------------------------
// MÉTODOS DE BUSCA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna o vertice ou NULL se nao encontrar

vertice procuraVert(lista l, char *p) {
	// printf("Procura lista...\n");
  noh aux = l->ini;
	// if (!aux)
	// 	printf("lista vazia\n");
  while(aux) {
		vertice v = (vertice) aux->cont;
		// printf("Compara: %s com %s\n", v->nome, p);
    if (strcmp(v->nome,p) == 0)
      return v;
    
    aux = aux->prox;
  }
  return NULL;
}

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna a aresta ou NULL se nao encontrar

aresta procuraAres(noh aux, vertice v) {
	if (!aux)
		return NULL;
	aresta a = (aresta) aux->cont;
	// printf("Comparando %s com %s\n", v->nome, a->vert->nome);
	if (strcmp(v->nome,a->vert->nome) == 0)
		return a;
	return procuraAres(aux->prox,v);
}

//------------------------------------------------------------------------------
// MÉTODOS DE LEITURA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input
// 
// devolve o grafo lido,
//         ou 
//         NULL, em caso de erro 

grafo leGrafo(FILE *input) {
  if (TEST) printf("Lendo grafo do arquivo...\n");
	Agraph_t *g = agread(input, NULL);
  grafo gr = criaGrafo(agnameof(g),agisdirected(g),agnnodes(g),agnedges(g));

	insereVert(g,gr);
	constroiViz(g,gr);
  if (TEST) imprimeGrafo(gr);

	agclose(g);
	agfree(g,NULL);
  if (TEST) printf("Grafo lido.\n");

	return gr;
}

//------------------------------------------------------------------------------
// MÉTODOS DE ESCRITA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 

grafo escreveGrafo(FILE *output, grafo g) {
  imprimeGrafo(g);
  return g;
}

//------------------------------------------------------------------------------
// MÉTODOS DE DESTRUIÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroiGrafo(grafo g) {
	liberaLista(g->vert);
	free(g);
  return 0;
}

//------------------------------------------------------------------------------
// MÉTODOS DE COLORAÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// devolve um número entre 0 e o número de vertices de g

unsigned int cor(vertice v, grafo g) {
	return 0;
}

void adicionaRotulo(char *rotulo, long l) {
	char str[10];
	sprintf(str, "%ld", l);
	strcat(rotulo,str);
}

//------------------------------------------------------------------------------
// preenche o vetor v (presumidamente um vetor com n_vertices(g)
// posições) com os vértices de g ordenados de acordo com uma busca em
// largura lexicográfica sobre g a partir de r e devolve v

vertice *buscaLexicografica(grafo g, vertice *v) {
	if (TEST) printf("------------------------------------------\n");
	lista conjuntoVertices = copiaLista(g->vert);
	if (TEST) imprimeConjunto(conjuntoVertices);
	vertice r = (vertice) conjuntoVertices->ini->cont;
	adicionaRotulo(r->rotulo,g->v);
	if (TEST) printf("inicia %s com rotulo %ld\n", r->nome, g->v);

	// while(conjuntoVertices->tam > 0) {
	// 	vertice maior = buscaMaiorRotulo(conjuntoVertices,1);
	// 	if (TEST) imprimeConjunto(conjuntoVertices);
	// 	for (noh aux = maior->vizinhos->ini; aux != NULL; aux = aux->prox) {
	// 		aresta a = (aresta) aux->cont;
	// 		if (procuraVert(conjuntoVertices,a->vert->nome) == NULL)
	// 			continue;
	// 		k = (long*) malloc(sizeof(long));
	// 		*k = conjuntoVertices->tam;
	// 		insereLista(a->vert->rotulo,k);
	// 		if (TEST) printf("inserido em %s o rotulo %ld\n", a->vert->nome, conjuntoVertices->tam);
	// 	}
	// }

	// conjuntoVertices = copiaLista(g->vert);

	// int i = 0;
	
	// while(conjuntoVertices->tam > 0) {
	// 	vertice maior = buscaMaiorRotulo(conjuntoVertices,1);
	// 	v[i++] = maior;
	// }

	// printf("v=[");
	// for (i = 0; i < g->v; i++) {
	// 	printf("%s", v[i]->nome);
	// 	if (i < g->v - 1)
	// 		printf(",");
	// }
	// printf("]\n");

	return v;
}

char* convertLongToString(long i) {
	return i + '0';
}

void imprimeConjunto(lista conjuntoVertices) {
	printf("conjuntoVertices=[");
	for(noh aux = conjuntoVertices->ini; aux != NULL; aux = aux->prox) {
		vertice r = (vertice) aux->cont;
		printf("%s", r->nome);
		if (aux->prox != NULL)
			printf(",");
	}
	printf("] | tamanho=%ld\n", conjuntoVertices->tam);
}

vertice buscaMaiorRotulo(lista conjuntoVertices, int remove) {
	noh maiorNo = conjuntoVertices->ini;
	vertice maior = (vertice) maiorNo->cont;
	if (TEST) printf("inicia maior como %s e tam do conj=%ld\n", maior->nome, conjuntoVertices->tam);
	if (conjuntoVertices->tam > 1) {
		for (noh aux = conjuntoVertices->ini->prox; aux != NULL; aux = aux->prox) {
			vertice comp = (vertice) aux->cont;
			if (TEST) printf("compara %s com %s\n", comp->nome, maior->nome);
			if (comparaRotulo(comp->rotulo,maior->rotulo) > 0) {
				if (TEST) printf("%s é maior que %s\n", comp->nome, maior->nome);
				maiorNo = aux;
				maior = comp;
			}
		}
	}
	if (remove) 
		removeListaEspec(conjuntoVertices,maiorNo);
	if (TEST) {
		printf("%s é o maior", maior->nome);
		if (remove)
			printf(" e foi removido\n");
		else
			printf("\n");
	}
	return maior;
}

int comparaRotulo(lista r1, lista r2) {
	if (r1->tam == 0)
		return -1;
	noh aux1 = r1->ini;
	noh aux2 = r2->ini;
	while(aux1 != NULL || aux2 != NULL) {
		if (aux1 == NULL)
			return -1;
		else
			return 1;
		long *i = (long*) aux1->cont;
		long *j = (long*) aux2->cont;
		printf("%ld com %ld\n", *i, *j);
		if (*i > *j)
			return 1;
		else if (*i < *j)
			return -1;
		else {
			aux1 = aux1->prox;
			aux2 = aux2->prox;
		}
	}
	return 0;
}

// char* transformaRotulo(lista l) {
// 	for (noh aux = l->ini; aux != NULL; aux = aux->prox) {

// 	}
// }

//------------------------------------------------------------------------------
// colore os vértices de g de maneira "gulosa" segundo a ordem dos
// vértices em v e devolve o número de cores utilizado
//
// ao final da execução,
//     1. cor(v,g) > 0 para todo vértice de g
//     2. cor(u,g) != cor(v,g), para toda aresta {u,v} de g

unsigned int colore(grafo g, vertice *v) {
	return 0;
}

//------------------------------------------------------------------------------