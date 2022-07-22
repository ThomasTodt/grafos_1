#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------
grafo le_grafo(void) 
{
  return agread(stdin, NULL); 
}
//------------------------------------------------------------------------------
void destroi_grafo(grafo g) 
{
  //return agclose(g);
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) 
{
  agwrite(g, stdout);
  return g;
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) 
{
  return agnnodes(g);
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) 
{
  return agnedges(g);
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) 
{
  // return agdegree(g, v, 0, 0);
  return agcountuniqedges(g, v, 0, 0); // considera loop como uma aresta apenas
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  
{

  vertice atual = agfstnode(g);
  int grauMax = grau(atual, g);

  vertice ultimo = aglstnode(g);


  while (atual != ultimo)
  {
    int grauAtual = grau(atual, g);

    if (grauAtual > grauMax)
      grauMax = grauAtual;

    atual = agnxtnode(g, atual);
  }

  
  return grauMax;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  
{
  vertice atual = agfstnode(g);
  int grauMin = grau(atual, g);

  vertice ultimo = aglstnode(g);


  while (atual != ultimo)
  {
    int grauAtual = grau(atual, g);

    if (grauAtual < grauMin)
      grauMin = grauAtual;

    atual = agnxtnode(g, atual);
  }

  
  return grauMin;  
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g)
{
  vertice atual = agfstnode(g);
  int total = 0;

  vertice ultimo = aglstnode(g);

  while (atual != ultimo)
  {
    total += grau(atual, g);
    atual = agnxtnode(g, atual);
  }

  // Meio estranho retornar int, faria mais sentido retornar um float.
  return total / n_vertices(g);
}

// -----------------------------------------------------------------------------
int regular(grafo g)
{
  return 0;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  
  return NULL;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}

