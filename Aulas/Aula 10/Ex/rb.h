//
// Created by Vanessa on 08/06/2022.
//

#ifndef LISTA_8_RB_H
#define LISTA_8_RB_H

typedef struct arvore rb;

typedef struct no no;

//Cria uma nova árvore inicializando a sentinela
rb* criaArvore();

//Popula uma árvore rubro-negra a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(rb* arv, char* nomeArquivo);

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(rb* arv, int chave);

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(rb* arv, int chave);

//Percorrimento em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(no* raiz);

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no* recuperaNo(rb* arv, int chave);

//Imprime a chave do nó, sua cor, as chaves de seus filhos e do seu pai
//Se o nó não tiver filho da esquerda e/ou da direita, imprime NULO
//Se o pai for a sentinela, imprime Sentinela
void imprimeNo(rb* arv, no* atual);

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(rb* arv);

//Retorna a raiz da árvore (filho direita da sentinela)
no* getRaiz(rb* arv);

//Retorna a altura da árvore
int getAltura(no* raiz);

//******************FUNÇÕES DE BALANCEAMENTO***********************//
//rotação à esquerda no nó desbalanceado
void rotacaoEsq(rb* arv, no* noDesbalanceado);

//rotação à direita no nó desbalanceado
void rotacaoDir(rb* arv, no* noDesbalanceado);

//Verifica se houve desbalanceamento na inserção
//Se houve, faz o balanceamento
//Implementação do RB-INSERT-FIXUP(T, z) do Cormen
void balanceamentoInsercao(rb* arv, no* novoNo);


//Verifica se houve desbalanceamento na remoção
//Se houve, faz o balanceamento
//sucessor é o nó que ficou no lugar do nó removido
void balanceamentoRemocao(rb* arv, no* sucessor, no* pai, int chave);

#endif //LISTA_8_RB_H