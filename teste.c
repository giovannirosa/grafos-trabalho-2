#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  // monta grafo lendo entrada do stdin
  grafo g = leGrafo(stdin);

  if (!g)
    return 1;

  // ordena vertices em ordem lexicográfica
  char **v = buscaLexicografica(g, malloc((long unsigned int)g->v*sizeof(char)));

  // colore os vertices de acordo com a ordem
  colore(g, v);

  // escreve resultado do grafo colorido
  escreveGrafo(g);

  free(v);
  return !destroiGrafo(g);
}
