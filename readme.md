# Grafos Trabalho 2

Trabalho 2 da matéria de Grafos do primeiro semestre de 2018, Universidade Federal do Paraná - UFPR.

## Início

Existe um makefile neste diretório com os seguintes comandos disponíveis:

* make: compila os arquivos teste.c, grafo.c, lista.c e produz o executável teste
* make clean: limpa os arquivos .o e teste
* make rebuild: make clean + make

### Pré-requisitos

É necessario ter o gcc e a biblioteca cgraph-dev instalada.

## Testando

É possível testar o programa com um passo a passo e com um modo simplificado, os dois tendo stdout como saída.

### Como ativar os testes

Existem duas variáveis que podem ativar duas funcionalidades de teste que estão no arquivo grafo.h.

* TEST: assinando o valor 1, será impresso o passo a passo do código para facilitar o rastreamento.
* SIMPLIFICADO: assinando o valor 1, será impresso um grafo de saída simplificado para facilitar na verificação.

Utilize o comando make rebuild após mudar o valor dessas variáveis para compilar com mais agilidade.

Exemplo com entrada 4.dot:
```
SIMPLIFICADO = 0
//Foram usadas 4 cores distintas: #0000FF, #FF0000, #00FF00, #FF00FF
strict graph third {
  A [color="#0000FF"]
  B [color="#FF0000"]
  F [color="#00FF00"]
  C [color="#00FF00"]
  E [color="#FF00FF"]
  D [color="#FF0000"]
  G [color="#0000FF"]
  H [color="#00FF00"]
  I [color="#0000FF"]
  J [color="#FF0000"]
  A -- B 
  A -- F 
  B -- A 
  B -- F 
  B -- C 
  B -- E 
  B -- G 
  F -- A 
  F -- B 
  F -- E 
  F -- G 
  C -- B 
  C -- E 
  C -- D 
  E -- B 
  E -- F 
  E -- C 
  E -- G 
  E -- D 
  D -- C 
  D -- E 
  G -- B 
  G -- F 
  G -- E 
  G -- H 
  H -- G 
  H -- I 
  H -- J 
  I -- H 
  I -- J 
  J -- H 
  J -- I 
}
```
```
SIMPLIFICADO = 1
//Foram usadas 4 cores distintas: #0000FF, #FF0000, #00FF00, #FF00FF
strict graph third {
  A[#0000FF]->B->F
  B[#FF0000]->A->F->C->E->G
  F[#00FF00]->A->B->E->G
  C[#00FF00]->B->E->D
  E[#FF00FF]->B->F->C->G->D
  D[#FF0000]->C->E
  G[#0000FF]->B->F->E->H
  H[#00FF00]->G->I->J
  I[#0000FF]->H->J
  J[#FF0000]->H->I
}
```

### Como visualizar os grafos de saída

Para facilitar a correção é recomendado a utilização dos seguintes comandos:
```
./teste < 4.dot > cor.dot
dot -Tps cor.dot -o outfile.ps
```

Isso irá produzir um arquivo de imagem do grafo.
**Note que essa geração só é possível com os modos TESTE e SIMPLIFICADO desativados!!!!!!**

## Bibliotecas Utilizadas

* [gcc](https://gcc.gnu.org/) - The GNU Compiler Collection
* [Graphviz](https://graphviz.org/) - Graphviz is open source graph visualization software

## Autor

* **Giovanni Rosa** - [giovannirosa](https://github.com/giovannirosa)

## Licença

Código aberto, qualquer um pode usar para qualquer propósito.

## Reconhecimentos

* C não é produtivo, gastei 80% do meu tempo gerenciando memória e 20% resolvendo o problema proposto

## Bugs

Nenhum bug aparente com os testes realizados com os arquivos 1.dot, 2.dot, 3.dot, 4.dot.