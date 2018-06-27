#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = leGrafo(stdin);

  if (!g)
    return 1;

  long n = g->v;

  vertice *v = buscaLexicografica(g, malloc((long unsigned int)n*sizeof(vertice)));

  // printf("Foram usadas %d cores: ", colore(g, v));

  // int penultimo = n - 1;
  // for (int i = 0; i < penultimo; i++)
  //   printf("%d, ", cor(v[i], g));

  // printf("%d\n\n", cor(v[penultimo], g));

  escreveGrafo(stdout, g);

  free(v);

  return !destroiGrafo(g);
}
