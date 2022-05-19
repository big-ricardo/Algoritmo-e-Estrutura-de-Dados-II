//
// Created by Vanessa on 17/05/2022.
//

#ifndef LISTA_6_ABP_H
#define LISTA_6_ABP_H

typedef struct arvore abp;

typedef struct no no;

//Cria uma nova árvore inicializando a sentinela
abp *criaArvore();

//Popula uma árvore binária de pesquisa a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(abp *arv, char *nomeArquivo);

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(abp *arv, int chave);

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(abp *arv, int chave);

//Percorrimento em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(no *raiz);

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no *recuperaNo(abp *arv, int chave);

//Imprime a chave do nó, as chaves de seus filhos e do seu pai
//Se o nó não tiver filho da esquerda e/ou da direita, imprime NULO
//Se o pai for a sentinela, imprime Sentinela
void imprimeNo(no *atual);

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(abp *arv);

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(abp *arv);

#endif //LISTA_6_ABP_H
