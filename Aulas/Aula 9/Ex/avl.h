//
// Created by Vanessa on 23/05/2022.
//

#ifndef LISTA_7_AVL_H
#define LISTA_7_AVL_H


typedef struct arvore avl;

typedef struct no no;

//Cria uma nova árvore inicializando a sentinela
avl *criaArvore();

//Popula uma árvore binária de pesquisa a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(avl *arv, char *nomeArquivo);

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(avl *arv, int chave);

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(avl *arv, int chave);

//Percorrimento em pré-ordem
//printf("%d: %d\t", raiz->chave, raiz->fb);
void percorre(no *raiz);

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no *recuperaNo(avl *arv, int chave);

//Imprime a chave do nó, as chaves de seus filhos e do seu pai
//Se o nó não tiver filho da esquerda e/ou da direita, imprime NULO
//Se o pai for a sentinela, imprime Sentinela
void imprimeNo(no *atual);

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(avl *arv);

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(avl *arv);

//Função recursiva que retorna a altura da árvore
//A altura é maior distância entre a raiz e uma folha
int getAltura(no *raiz);

//******************FUNÇÕES DE BALANCEAMENTO ***************************//
//atualiza o valor do fator de balanceamento dos nós após a inserção de um nó
//condições de parada : após ajuste do FB => chegar no nó raiz ou o nó ficar com fb 0, 2 ou -2
void atualizaFB_Insercao(avl *arv, no *novoNo);

//atualiza o valor do fator de balanceamento dos nós após a remoção de um nó
//condições de parada : após ajuste do FB => chegar na sentinela ou o nó ficar com fb 1, -1, 2 ou -2
void atualizaFB_Remocao(avl *arv, no *pai, int chave);

//verifica a estratégia de balanceamento do nó e ajusta o fator de balanceamento
void balanceamento(avl *arv, no *noDesbalanceado);

//rotação à esquerda no nó desbalanceado
void rotacaoEsq(avl *arv, no *noDesbalanceado);

//rotação à direita no nó desbalanceado
void rotacaoDir(avl *arv, no *noDesbalanceado);





#endif //LISTA_7_AVL_H
