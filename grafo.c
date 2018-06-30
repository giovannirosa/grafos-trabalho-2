#include "grafo.h"

// vetor de cores hexadecimais HEX escolhidas para criar distancia visual
static const char *HEX[22] = {"#00FF00",
															"#FF0000",
															"#0000FF",
															"#FF00FF",
															"#FFFF00",
															"#00FFFF",
															"#DDDDDD",
															"#000000",
															"#00000F",
															"#000F00",
															"#0F0000",
															"#888888",
															"#000088",
															"#008800",
															"#880000",
															"#880088",
															"#888800",
															"#008888",
															"#44DD57",
															"#34FF88",
															"#DDAA56",
															"#B14512"};

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
			printf("  %s [color=\"%s\"]\n", v->nome, v->cor);
		}
		if (ares)
			imprimeAres(v->vizinhos->ini,v);
	} else {
		printf("  %s[%s]", v->nome, v->cor);
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
		printf("  %s -- %s \n", v->nome, a->vert->nome);
	} else {
		printf("->%s", a->vert->nome);
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
  vert->rotulo = malloc(sizeof(char));
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

grafo escreveGrafo(grafo g) {
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
// busca vertice pelo nome no grafo e devolve sua cor

const char* cor(char* vertNome, grafo g) {
	vertice vert = procuraVert(g->vert,vertNome);
	return vert->cor;
}

//------------------------------------------------------------------------------
// concatena um numero ao rotulo do vertice

void adicionaRotulo(char *rotulo, long l) {
	char str[10];
	sprintf(str, "%ld", l);
	strcat(rotulo,str);
}

//------------------------------------------------------------------------------
// preenche o vetor v (presumidamente um vetor com n_vertices(g)
// posições) com os vértices de g ordenados de acordo com uma busca em
// largura lexicográfica sobre g a partir de r e devolve v

char **buscaLexicografica(grafo g, char **v) {
	if (TEST) printf("------------------------------------------\n");
	lista conjuntoVertices = copiaLista(g->vert);
	if (TEST) imprimeConjunto(conjuntoVertices);
	vertice r = (vertice) conjuntoVertices->ini->cont;
	adicionaRotulo(r->rotulo,g->v);
	if (TEST) printf("inicia %s com rotulo %ld\n", r->nome, g->v);

	// primeira iteração para atribuir os rótulos
	while(conjuntoVertices->tam > 0) {
		vertice maior = buscaMaiorRotulo(conjuntoVertices);
		if (TEST) imprimeConjunto(conjuntoVertices);
		for (noh aux = maior->vizinhos->ini; aux != NULL; aux = aux->prox) {
			aresta a = (aresta) aux->cont;
			if (procuraVert(conjuntoVertices,a->vert->nome) == NULL)
				continue;
			adicionaRotulo(a->vert->rotulo,conjuntoVertices->tam);
			if (TEST) printf("inserido em %s o rotulo %ld\n", a->vert->nome, conjuntoVertices->tam);
		}
	}

	if (TEST) printf("------------------------------------------\n");
	conjuntoVertices = copiaLista(g->vert);
	if (TEST) imprimeConjunto(conjuntoVertices);

	// segunda iteração para obter a ordem lexicográfica
	int i = 0;
	while(conjuntoVertices->tam > 0) {
		vertice maior = buscaMaiorRotulo(conjuntoVertices);
		if (TEST) imprimeConjunto(conjuntoVertices);
		v[i] = (char*) malloc(sizeof(maior->nome) / sizeof(char*));
		v[i++] = maior->nome;
	}

	if (TEST) {
		printf("v=[");
		for (i = 0; i < g->v; i++) {
			printf("%s", v[i]);
			if (i < g->v - 1)
				printf(",");
		}
		printf("]\n");
	}

	// zera os rótulos para manter a consistencia
	zeraRotulos(g);

	return v;
}

//------------------------------------------------------------------------------
// caminha pelo grafo e zera os rótulos de todos os vertices

void zeraRotulos(grafo g) {
	for (noh aux = g->vert->ini; aux != NULL; aux = aux->prox) {
		vertice v = (vertice) aux->cont;
		free(v->rotulo);
		v->rotulo = malloc(sizeof(char));
	}
}

//------------------------------------------------------------------------------
// imprime conjunto de vertices

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

//------------------------------------------------------------------------------
// busca maior rotulo entre todos os vertices do conjunto usando strcmp()

vertice buscaMaiorRotulo(lista conjuntoVertices) {
	noh maiorNo = conjuntoVertices->ini;
	vertice maior = (vertice) maiorNo->cont;
	if (TEST) printf("inicia maior como %s com rotulo %s e tam do conj=%ld\n", maior->nome, maior->rotulo, conjuntoVertices->tam);
	if (conjuntoVertices->tam > 1) {
		for (noh aux = conjuntoVertices->ini->prox; aux != NULL; aux = aux->prox) {
			vertice comp = (vertice) aux->cont;
			if (TEST) printf("compara %s [%s] com %s [%s]\n", comp->nome, comp->rotulo, maior->nome, maior->rotulo);
			if (strcmp(comp->rotulo,maior->rotulo) > 0) {
				if (TEST) printf("%s é maior que %s\n", comp->nome, maior->nome);
				maiorNo = aux;
				maior = comp;
			}
		}
	}
	removeListaEspec(conjuntoVertices,maiorNo);
	if (TEST) printf("%s é o maior e foi removido\n", maior->nome);
	if (TEST) printf("------------------------------------------\n");
	return maior;
}

//------------------------------------------------------------------------------
// colore os vértices de g de maneira "gulosa" segundo a ordem dos
// vértices em v e devolve o número de cores utilizado
//
// ao final da execução,
//     1. cor(v,g) > 0 para todo vértice de g
//     2. cor(u,g) != cor(v,g), para toda aresta {u,v} de g

int colore(grafo g, char **v) {
	for (int i = 0; i < g->v; i++) {
		char *vertNome = v[i];
		vertice vert = procuraVert(g->vert,vertNome);
		const char *c = garanteCor(vert,HEX[0],0);
		vert->cor = c;
		if (TEST) printf("assinada cor %s para vertice %s\n", c, vert->nome);
	}

	const char** coresUsadas = malloc(sizeof(char));
	coresUsadas[0] = malloc(7*sizeof(char));
	vertice vert = (vertice) g->vert->ini->cont;
	int count = 1;
	coresUsadas[0] = vert->cor;
	for (noh aux = g->vert->ini->prox; aux != NULL; aux = aux->prox) {
		vert = (vertice) aux->cont;
		const char *cor = vert->cor;
		int achou = 0;
		for (int i = 0; i < count; i++) {
			if (strcmp(cor,coresUsadas[i]) == 0) {
				achou = 1;
				break;
			}
		}
		if (!achou) {
			coresUsadas[count] = malloc(7*sizeof(char));
			coresUsadas[count] = cor;
			count++;
		}
	}

	printf("//Foram usadas %d cores distintas: ", count);

	for (int i = 0; i < count-1; i++)
		printf("%s, ", coresUsadas[i]);
	printf("%s\n", coresUsadas[count-1]);

	free(coresUsadas);

	return count;
}

//------------------------------------------------------------------------------
// garante que sera escolhida uma cor que nao é utilizada pelos vizinhos do
// vertice de maneira recursiva, cada nova tentativa escolhe uma cor do
// vetor de cores hexadecimais HEX definido no topo desse arquivo

const char *garanteCor(vertice vert, const char *novaCor, int tentativa) {
	for (noh aux = vert->vizinhos->ini; aux != NULL; aux = aux->prox) {
		aresta ares = (aresta) aux->cont;
		if (TEST) printf("compara [%s] com [%s]\n", ares->vert->cor,novaCor);
		if (ares->vert->cor != NULL && strcmp(ares->vert->cor,novaCor) == 0) {
			tentativa++;
			if (TEST) printf("cores iguais tentativa %d com nova cor %s\n",tentativa, HEX[tentativa]);
			return garanteCor(vert,HEX[tentativa],tentativa);
		}
	}
	return novaCor;
}

//------------------------------------------------------------------------------