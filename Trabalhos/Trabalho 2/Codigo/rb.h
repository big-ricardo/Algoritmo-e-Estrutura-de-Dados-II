//
// Created by Vanessa on 08/06/2022.
//

#ifndef LISTA_8_RB_H
#define LISTA_8_RB_H

typedef struct rb rb;

typedef struct noRb noRb;

struct noRb {
    int chave;
    char cor;
    noRb* esq;
    noRb* dir;
    noRb* pai;
};

struct rb {
    noRb* sentinela;
    noRb* sentinelaFolha;
    int numElementos;
};

//Cria uma nova árvore inicializando a sentinela
rb* criaArvoreRb();

//Popula uma árvore rubro-negra a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(rb* arv, char* nomeArquivo);

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(rb* arv, int chave);

//Remove elementos de uma árvore rubro-negra a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a remoção e/ou leitura do arquivo
//Retorna 0 caso contrário
int removeElementos(rb* arv, char* nomeArquivo);

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(rb* arv, int chave);

//Percorrimento em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(noRb* raiz);

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
noRb* recuperaNo(rb* arv, int chave);

//Imprime a chave do nó, sua cor, as chaves de seus filhos e do seu pai
//Se o nó não tiver filho da esquerda e/ou da direita, imprime NULO
//Se o pai for a sentinela, imprime Sentinela
void imprimeNo(rb* arv, noRb* atual);

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(rb* arv);

//Retorna a raiz da árvore (filho direita da sentinela)
noRb* getRaiz(rb* arv);

//Retorna a altura da árvore
int getAltura(noRb* raiz);

//Retorna a sentinelaFolha
noRb* getNULL(rb* arv);

//******************FUNÇÕES DE BALANCEAMENTO***********************//
//rotação à esquerda no nó desbalanceado
void rotacaoEsq(rb* arv, noRb* noDesbalanceado);

//rotação à direita no nó desbalanceado
void rotacaoDir(rb* arv, noRb* noDesbalanceado);

//Verifica se houve desbalanceamento na inserção
//Se houve, faz o balanceamento
//Implementação do RB-INSERT-FIXUP(T, z) do Cormen
void balanceamentoInsercao(rb* arv, noRb* novoNo);


//Verifica se houve desbalanceamento na remoção
//Se houve, faz o balanceamento
//sucessor é o nó que ficou no lugar do nó removido
void balanceamentoRemocao(rb* arv, noRb* sucessor, noRb* pai, int chave);

#endif //LISTA_8_RB_H
