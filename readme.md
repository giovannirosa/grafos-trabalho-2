# Grafos Trabalho 2

Trabalho 2 da matéria de Grafos do primeiro semestre de 2018, Universidade Federal do Paraná - UFPR.

## Início

Existe um makefile neste diretório com os seguintes comandos disponíveis:

* make: compila os arquivos teste.c, grafo.c, lista.c e produz o executável teste
* make clean: limpa os arquivos .o
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

Exemplo com entrada 2.dot:
```
SIMPLIFICADO = 0
graph recomendacoes {
  c1 [tipo=c]
  c2 [tipo=c]
  c3 [tipo=c]
  pa [tipo=p]
  pb [tipo=p]
  pc [tipo=p]
  c2 -- pa [label=1] (nesse caso label=peso, só foi alterado para geração de imagem)
  c3 -- pc [label=1]
  pa -- c2 [label=1]
  pc -- c3 [label=1]
}
```
```
SIMPLIFICADO = 1
graph recomendacoes {
  c1
  c2->pa[1]
  c3->pc[1]
  pa->c2[1]
  pb
  pc->c3[1]
}
```

### Como visualizar os grafos de saída

Para facilitar a correção é recomendado a utilização dos seguintes comandos:
```
./teste < 3.dot > rec.dot
dot -Tps rec.dot -o outfile.ps
```

Isso irá produzir um arquivo de imagem do grafo.
**Note que essa geração só é possível com o modo SIMPLIFICADO desativado!!!!!!**

## Bibliotecas Utilizadas

* [gcc](https://gcc.gnu.org/) - The GNU Compiler Collection
* [Graphviz](https://graphviz.org/) - Graphviz is open source graph visualization software

## Autor

* **Giovanni Rosa** - [giovannirosa](https://github.com/giovannirosa)

## Licença

Código aberto, qualquer um pode usar para qualquer propósito.

## Reconhecimentos

* C não é produtivo
* A biblioteca cgraph é meio bugada

## Bugs

Não pude utilizar a biblioteca cgraph para escrever o grafo de saída, aparentemente existe algum bug quando tento utilizar o método agnode(). Com isso, fiz a saída simular o trabalho da biblioteca.