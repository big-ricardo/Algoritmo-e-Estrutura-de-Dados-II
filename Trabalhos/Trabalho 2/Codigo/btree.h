//
// Created by Vanessa on 22/06/2022.
//

#ifndef LISTA_9_BTREE_H
#define LISTA_9_BTREE_H

typedef struct noBt noBt;

typedef struct btree btree;

struct noBt {
    int* chaves;
    noBt** ponteiros;
    noBt* pai;
    int folha;
    int ocupacao;
};

struct btree {
    int ordem;
    noBt* raiz;
};


//Função que aloca e inicializa um novo nó
noBt* alocaNo(int ordem);

//Função que aloca e inicializa uma nova árvore com uma raiz alocada, porém vazia.
//Árvore B tradicional. A ordem m deve ser sempre par. Caso contrário, retorna NULL.
btree* criaArvoreBt(int m);

//Função que retorna a raiz da árvore
noBt* retornaRaiz(btree* arvore);

//Função recursiva que imprime a árvore por profundidade
//Raiz, filho da esquerda até chegar na folha. E sobe imprimindo os filhos em sequência
void imprimeArvore(noBt* atual, int filho);

//Função recursiva que retorna o nó onde o elemento está na árvore
noBt* buscaElemento(noBt* atual, int valor);

//Função que insere um novo elemento na árvore.
//Encontra a folha correta, realiza a inserção em árvore B tradicional
//Ou seja, se a folha estiver cheia, primeiro realiza o split e depois insere
//Se houve a inserção, retorna 1. Caso contrário, retorna -1
int insereElemento(btree* arvore, int valor);

//Função que realiza o split no noDesbal. A variável valor guarda o elemento que está sendo inserido (e que causou o split)
//Função chamada pela função insereElemento
//Sempre sobe o elemento do meio para o pai (m é sempre par).
//Caso o pai esteja cheio, a função se chama recursivamente.
noBt* split(btree* arvore, noBt* noDesbal, int valor);

//Função que remove um elemento da B-Tree
//Na remoção por cópia, usar o predecessor
//No caso de rotação e merge, tentar primeiro o irmão da esquerda e depois o da direita
//Se houve a remoção, retorna 1. Caso contrário, retorna -1
int removeElemento(btree* arvore, int valor);


//Função que implementa a rotação, levanto um elemento do pai para o nóDesbal e subindo um elemento do no irmão para o pai
// A variável posPai guarda a posição do ponteiro do pai que aponta para o nó noDesbal
void rotacao(noBt* noDesbal, noBt* irmao, int posPai);

//Função que implementa o merge do nó Desbal com seu irmão da esquerda ou da direita
//Se a variãvel posPai é maior que zero, o merge acontece com o irmão da esquerda
//Caso contrário, com o irmão da direita
noBt* merge(noBt* noDesbal, int posPai);


//Função que lê dados do arquivo nomeArquivo e os insere ou remove da B-Tree arvore
//Se o status for "i", a função deve inserir todos os elementos do arquivo na árvore
//Se o status for "r", a função deve remover todos os elementos do arquivo da árvore
void manipulaBTree(btree* arvore, char* nomeArquivo, char status);


#endif //LISTA_9_BTREE_H
