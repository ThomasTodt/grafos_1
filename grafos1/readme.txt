Um grande número de funções já tinham correspondentes na biblioteca cgraph. Elas
são:
 - le_grafo()
 - destroi_grafo()
 - escreve_grafo()
 - n_vertices()
 - n_arestas()
 - grau()

Dessas, apenas a le_grafo() tivemos que modificar para inicializarmos o record
que armazena dados auxiliares para as funções conexo() e bipartido().

As funções grau_maximo() e grau_mínimo() são bem simples, apenas iteramos por
todos os vértices do grafo, guardando o maior/menor grau.

Dado o teorema que a soma de graus é igual a duas vezes o número de arestas,
e que o grau médio é a soma dos graus dividido pelo número vértices, temos que o
grau médio é duas vezes o número de arestas dividido pelo número de vértices.
Assim podemos implementar grau_medio() sem iterar por todos os vértices (O(1)).

Para a função regular() também iteramos sobre todos os vértices, e, se temos um
vértice com grau diferente, retornamos 0. Se chegamos ao fim, todos o vértices
tem o mesmo grau e o grafo é regular.

Na função completo() checamos se o número de arestas é igual a v * (v - 1) / 2,
onde v é o número de vértices. Isso porque essa fórmula funciona se e somente se
o grafo é completo.

A função conexo() necessitou uma função auxiliar. A ideia é que se percorremos
os vizinhos de um vértice sempre obtemos um subgrafo conexo. Assim podemos
percorrer recursivamente os vizinhos dos vizinhos, até obter o subgrafo máximo
do componente. Então, se e somente se para todo vértice do grafo esse vértice
pertence ao subgrafo que achamos, o grafo é conexo.

A função bipartido() é parecida com a conexo() na maneira que percorremos o
grafo. A diferença é que, ao invés de só marcar se já percorremos o vértice
também marcamos a paridade do tamanho do caminho do vértice original até o que
estamos visitando (no código chamamos isso de 'cor'). Existe o teorema que todo
caminho entre dois vértices tem a mesma paridade se e somente se o grafo é
bipartido, assim se a paridade que iremos colocar é diferente da paridade já
colocada sabemos que o grafo não é bipartido.

Na função n_triangulos() utilizamos o fato de que o elemento m[i][j] da matriz
de adjacência elevada a 'n' representa o número de caminhos distintos do
vértice i até j no grafo. Como um triângulo é um caminho de tamanho 3 que sai de
i e chega em i, podemos olhar a diagonal i = j e somar seus valores. Porém dessa
forma estaremos contando triângulos iguais mais de uma vez, já que os triângulos
ABC, BCA, CAB, CBA, BAC, ACB são os mesmos. Por isso dividimos o resultado final
por 6.

A função matriz_adjacencia() é bem simples, iteramos por todos os pares de
vértices e checamos se existe uma aresta entre eles, se existe colocamos 1 na
posição correspondente, se não colocamos um 0.


Na função complemento() criamos um novo grafo e fazemos parecido com a função
matriz_adjacência(): iteramos todos pares de vértices, porém agora quando não
existe aresta entre os dois, criamos uma aresta no novo grafo.

