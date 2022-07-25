#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  escreve_grafo(g);

  printf("%d vertices\n", n_vertices(g));
  printf("%d arestas\n", n_arestas(g));
  printf("%d é o grau maximo\n", grau_maximo(g));
  printf("%d é o grau minimo\n", grau_minimo(g));
  printf("%d é o grau medio\n", grau_medio(g));

  if (regular(g))
    printf("é regular\n");
  else
    printf("não é regular\n");

  if (completo(g))
    printf("é completo\n");
  else
    printf("não é completo\n");

  if (conexo(g))
    printf("é conexo\n");
  else
    printf("não é conexo\n");

  if (bipartido(g))
    printf("é bipartido\n");
  else
    printf("não é bipartido\n");

  printf("%d triangulos\n", n_triangulos(g));

  printf("Matriz de adjacência:\n");
  int **m = matriz_adjacencia(g);
  for (int i = 0; i < n_vertices(g); i++) {
    for (int j = 0; j < n_vertices(g); j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
  grafo comp = complemento(g);
  //printf("complemento de g:\n");
  escreve_grafo(comp);

  destroi_grafo(comp);
  
  destroi_grafo(g);

  return 0;
}
