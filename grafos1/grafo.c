#include <stdio.h>
#include "grafo.h"

typedef struct {
  Agrec_t header;
  int contado;
} info_vertice;

typedef struct {
  Agrec_t header;
  int criada;
} info_aresta;

//------------------------------------------------------------------------------
grafo le_grafo(void) 
{
  return agread(stdin, NULL); 
}
//------------------------------------------------------------------------------
void destroi_grafo(grafo g) 
{
  return agclose(g);
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) 
{
  return agwrite(g, stdout);
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
  
  vertice atual = agfstnode(g);
  int grauReg = grau(atual, g);

  vertice ultimo = aglstnode(g);


  while (atual != ultimo)
  {
    int grauAtual = grau(atual, g);

    if (grauAtual != grauReg)
      return 0;

    atual = agnxtnode(g, atual);
  }


  return 1;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int backtrack_conexo(grafo g, vertice atual, int *contador_vertices) // funcao que auxilia a funcao "conexo"
{
  if (contador_vertices == 0)
    return 1;

  info_vertice *info;
  info = aggetrec(atual, "info_vertice", TRUE);

  if (info->contado == 0) // contabiliza o vertice
  {
    info->contado = 1;
    *contador_vertices--;


    for (vertice v = agnxtnode(g, atual); v; v = agnxtnode(g,v))
    {
      if ( agedge(g, atual, v, NULL, 0) );
      {
        if ( backtrack_conexo(g, v, contador_vertices) == 1 )
          return 1;
      }
    }

  }


  return 0;
}

int conexo(grafo g) 
{
  info_vertice *info;

  for (vertice v = agfstnode(g); v; v = agnxtnode(g,v))
  {
    info = agbindrec(v, "info_vertice", sizeof(info_vertice), TRUE);
    info->contado = 0;
  }

  int contador_vertices = n_vertices(g);

  return backtrack_conexo(g, agfstnode(g), &contador_vertices);
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
void multiplica_matriz_adjacencia(int **A, int **B, int **C, int tamanho)
{
  for (int i=0; i < tamanho; i++)
  {
    for (int j=0; j < tamanho; j++)
    {
      C[i][j] = 0;
      for (int k=0; k < tamanho; k++)
        C[i][j] += A[i][k] * B[k][j];
    }
  }
}

int n_triangulos(grafo g) 
{
  int **mat = matriz_adjacencia(g);
  int **mat2, **mat3;

  int tamanho = n_vertices(g);

  mat2 = malloc (tamanho * sizeof (int*)) ;
  for (int i=0; i < tamanho; i++)
    mat2[i] = malloc (tamanho * sizeof (int)) ;

  mat3 = malloc (tamanho * sizeof (int*)) ;
  for (int i=0; i < tamanho; i++)
    mat3[i] = malloc (tamanho * sizeof (int)) ;


  multiplica_matriz_adjacencia(mat, mat, mat2, tamanho);
  multiplica_matriz_adjacencia(mat, mat2, mat3, tamanho);


  int traco = 0 ;
  for (int i=0; i < tamanho; i++)
    traco += mat3[i][i];


  // liberar matrizes
  for (int i=0; i < tamanho; i++)
  {
    free(mat[i]);
    free(mat2[i]);
    free(mat3[i]);
  }
  free(mat);
  free(mat2);
  free(mat3);
  
  return traco;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) 
{
  Agnode_t *n;
  Agnode_t *m;
  Agedge_t *e;
  int i, j;
  int num_vertices = n_vertices(g);

  int **mat;

  mat = malloc (num_vertices * sizeof (int*)) ;

  for (i=0; i < num_vertices; i++)
    mat[i] = malloc (num_vertices * sizeof (int)) ;
  
  i=0;
  j=0;
  for (n = agfstnode(g); n; n = agnxtnode(g,n)) {
    j=0;
    for (m = agfstnode(g); m; m = agnxtnode(g,m)) {
      e = agedge(g,n,m,NULL,FALSE);


      if(e != NULL){
        mat[i][j]=1;
        printf("1");
      }
      else{
        mat[i][j]=0;
        printf("0");
      }
        
      j++;
    }

    printf("\n");
    i++;
  }
  
  return mat;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g)
{
  info_aresta *info;

  grafo h = agread( agwrite(g, stdin), stdin );

  // inicializa arestas (records)
  for (vertice v = agfstnode(h); v; v = agnxtnode(h,v))
  {
    for (Agedge_t *a = agfstedge(h, v); a; a = agnxtedge(h, a, v)) // inicializa mais de uma vez a mesma aresta?
    {
      info = agbindrec(v, "info_aresta", sizeof(info_aresta), TRUE);
      info->criada = 0 ;
    }
  }

  // cria arestas faltantes
  for (vertice v = agfstnode(h); v; v = agnxtnode(g,v))
  {
    for (vertice v2 = agfstnode(h); v2; v2 = agnxtnode(h, v2))
    {
      if (v != v2)
      {
        if ( ! agedge(h, v, v2, NULL , 0) ) // se nao existe aresta entre os vertices, faça:
        {
          Agedge_t *a = agedge(h, v, v2, NULL, 1); // cria aresta
          info = agbindrec(a, "info_aresta", sizeof(info_aresta), TRUE);
          info->criada = 1 ;
        }
      }
    }
  }

  // deleta arestas originais
  for (vertice v = agfstnode(h); v; v = agnxtnode(h, v))
  {
    for (vertice v2 = agfstnode(h); v2; v2 = agnxtnode(h, v2))
    {
      Agedge_t *a = agedge(h, v, v2, NULL, 0);
      info = aggetrec( a, "info_aresta", TRUE );
      if( info->criada == 0) // se aresta pertence ao grafo original:
        agdeledge(h, a);
    }
  }
  
  return h;
}
