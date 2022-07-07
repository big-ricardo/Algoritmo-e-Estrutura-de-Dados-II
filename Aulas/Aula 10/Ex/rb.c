#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

/*
  Luis Ricardo Albano Santos - 2021031844
  Matheus Martins Batista 2019005687
*/

struct no {
    int chave;
    char cor;
    no* esq;
    no* dir;
    no* pai;
};

struct arvore {
    no* sentinela;
    no* sentinelaFolha;
    int numElementos;
};

rb* criaArvore() {
    rb* arv = (rb*)malloc(sizeof(rb));

    no* sentinela = (no*)malloc(sizeof(no));

    no* sentinelaFolha = (no*)malloc(sizeof(no));

    if (arv == NULL || sentinela == NULL || sentinelaFolha == NULL) {
        printf("Erro ao alocar memória para a árvore.\n");
        return NULL;
    }


    sentinela->chave = -1000;
    sentinela->esq = NULL;
    sentinela->dir = sentinelaFolha;
    sentinela->pai = NULL;
    sentinela->cor = 'p';

    sentinelaFolha->chave = -2000;
    sentinelaFolha->esq = NULL;
    sentinelaFolha->dir = NULL;
    sentinelaFolha->pai = NULL;
    sentinelaFolha->cor = 'p';

    arv->sentinelaFolha = sentinelaFolha;
    arv->sentinela = sentinela;
    arv->numElementos = 0;
    return arv;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no* getRaiz(rb* arv) {
    return arv->sentinela->dir;
}

no* getNULL(rb* arv) {
    return arv->sentinelaFolha;
}

//Popula uma árvore binária de pesquisa a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(rb* arv, char* nomeArquivo) {
    FILE* arq;
    int num;

    arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return -1;
    }

    while (fscanf(arq, "%d", &num) != EOF) {
        insereNo(arv, num);
    }

    fclose(arq);
    return 0;
}

//Remove elementos de uma árvore rubro-negra a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a remoção e/ou leitura do arquivo
//Retorna 0 caso contrário
int removeElementos(rb* arv, char* nomeArquivo) {
    FILE* arq;
    int num;

    arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return -1;
    }

    while (fscanf(arq, "%d", &num) != EOF) {
        removeNo(arv, num);
    }

    fclose(arq);
    return 0;
}

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(rb* arv, int chave) {
    no* novoNo = (no*)malloc(sizeof(no));
    no* atual = getRaiz(arv);
    no* pai = NULL;

    novoNo->chave = chave;
    novoNo->esq = getNULL(arv);
    novoNo->dir = getNULL(arv);
    novoNo->pai = NULL;
    novoNo->cor = 'v';

    while (atual != getNULL(arv)) {
        pai = atual;
        if (chave < atual->chave) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    if (pai == NULL) {
        arv->sentinela->dir = novoNo;
        novoNo->pai = arv->sentinela;
        novoNo->cor = 'p';

        arv->numElementos++;

        return 0;
    }
    else {
        if (chave < pai->chave) {
            pai->esq = novoNo;
        }
        else {
            pai->dir = novoNo;
        }

        novoNo->pai = pai;
        arv->numElementos++;
    }

    if (pai->cor == 'v') {
        balanceamentoInsercao(arv, novoNo);
    }

    return 0;
}

int getAltura(no* raiz) {
    if ((raiz == NULL) || (raiz->esq == NULL && raiz->dir == NULL)) {
        return 0;
    }
    else { //retorna a pilha do lado com maior profundidade
        if (getAltura(raiz->esq) > getAltura(raiz->dir)) {
            return 1 + getAltura(raiz->esq);
        }
        else {
            return 1 + getAltura(raiz->dir);
        }
    }
}

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(rb* arv, int chave) {
    no* atual = getRaiz(arv);
    no* filho = NULL;
    no* aux = NULL;
    no* sucessor = NULL;

    if (atual == NULL) {
        printf("Erro: Árvore vazia\n");
        return -1;
    }

    while (atual != getNULL(arv) && atual->chave != chave) {
        if (chave < atual->chave) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    if (atual == getNULL(arv)) {
        printf("Erro: Elemento não encontrado\n");
        return -2;
    }

    if (atual->esq != getNULL(arv) && atual->dir != getNULL(arv)) {
        aux = atual->esq;
        while (aux->dir != getNULL(arv)) {
            aux = aux->dir;
        }
        atual->chave = aux->chave;
        atual = aux;
    }

    if (atual->dir != getNULL(arv)) {
        filho = atual->dir;
    }
    else {
        filho = atual->esq;
    }

    if (filho != getNULL(arv)) {
        filho->pai = atual->pai;
    }

    if (atual->pai == NULL) {
        arv->sentinela = filho;
    }
    else {
        if (atual == atual->pai->esq) {
            atual->pai->esq = filho;
        }
        else {
            atual->pai->dir = filho;
        }
        sucessor = filho;
    }

    char corAux = atual->cor;
    int auxChave = atual->chave;
    no* pai = atual->pai;

    free(atual);
    arv->numElementos--;

    if (corAux == 'p') {
        balanceamentoRemocao(arv, sucessor, pai, auxChave);
    }
    return 0;
}

//Percorrimento em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(no* raiz) {
    if (raiz->chave != -2000) {
        printf("%d: %c  ", raiz->chave, raiz->cor);
        percorre(raiz->esq);
        percorre(raiz->dir);
    }
}

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no* recuperaNo(rb* arv, int chave) {
    no* atual = arv->sentinela;

    while (atual != NULL && atual->chave != chave) {
        if (chave < atual->chave) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    return atual;
}

//Imprime a chave do nó, as chaves de seus filhos e do seu pai
//Se o nó não tiver filho da esquerda e/ou da direita, imprime NULO
//Se o pai for a sentinela, imprime Sentinela
void imprimeNo(rb* arv, no* atual) {
    if (atual != NULL) {
        printf("\n########################\n");
        printf("Chave : %d\n", atual->chave);
        printf("Cor: %c\n", atual->cor);
        if (atual->esq != getNULL(arv)) {
            printf("Filho Esq : %d\n", atual->esq->chave);
        }
        else {
            printf("Filho Esq : NULO\n");
        }
        if (atual->dir != getNULL(arv)) {
            printf("Filho Dir : %d\n", atual->dir->chave);
        }
        else {
            printf("Filho Dir : NULO\n");
        }
        if (atual->pai != getNULL(arv) && atual->pai->pai != getNULL(arv)) {
            printf("Pai : %d\n", atual->pai->chave);
        }
        else {
            printf("Pai : Sentinela\n");
        }
    }
}

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(rb* arv) {
    return arv->numElementos;
}

//Verifica se houve desbalanceamento na inserção
//Se houve, faz o balanceamento
//Implementação do RB-INSERT-FIXUP(T, z) do Cormen
void balanceamentoInsercao(rb* arv, no* novoNo) {
    while (novoNo->pai->cor == 'v') {
        no* avo = novoNo->pai->pai;

        if (novoNo->pai == avo->esq) {
            no* tio = avo->dir;
            if (tio->cor == 'v') {
                novoNo->pai->cor = 'p';
                tio->cor = 'p';
                avo->cor = 'v';
                novoNo = avo;
            }
            else {
                if (novoNo == novoNo->pai->dir) {
                    novoNo = novoNo->pai;
                    rotacaoEsq(arv, novoNo);
                }
                novoNo->pai->cor = 'p';
                avo->cor = 'v';
                rotacaoDir(arv, avo);
            }
        }
        else {
            no* tio = avo->esq;
            if (tio->cor == 'v') {
                novoNo->pai->cor = 'p';
                tio->cor = 'p';
                avo->cor = 'v';
                novoNo = avo;
            }
            else {
                if (novoNo == novoNo->pai->esq) {
                    novoNo = novoNo->pai;
                    rotacaoDir(arv, novoNo);
                }
                novoNo->pai->cor = 'p';
                avo->cor = 'v';
                rotacaoEsq(arv, avo);
            }
        }
    }

    getRaiz(arv)->cor = 'p';
}

//Verifica se houve desbalanceamento na remoção
//Se houve, faz o balanceamento
//sucessor é o nó que ficou no lugar do nó removido
void balanceamentoRemocao(rb* arv, no* sucessor, no* pai, int chave) {
    while (sucessor->cor == 'p' && sucessor != getRaiz(arv)) {
        if (chave <= pai->chave) {
            no* irmao = pai->dir;
            if (irmao->cor == 'v') {
                irmao->cor = 'p';
                pai->cor = 'v';
                rotacaoEsq(arv, pai);
                irmao = pai->dir;
            }
            if (irmao->esq->cor == 'p' && irmao->dir->cor == 'p') {
                irmao->cor = 'v';
                sucessor = pai;
                pai = pai->pai;
            }
            else {
                if (irmao->dir->cor == 'p') {
                    irmao->esq->cor = 'p';
                    irmao->cor = 'v';
                    rotacaoDir(arv, irmao);
                    irmao = pai->dir;
                }
                irmao->cor = pai->cor;
                pai->cor = 'p';
                irmao->dir->cor = 'p';
                rotacaoEsq(arv, pai);
                sucessor = getRaiz(arv);
                pai = NULL;
            }
        }
        else {
            no* irmao = pai->esq;
            if (irmao->cor == 'v') {
                irmao->cor = 'p';
                pai->cor = 'v';
                rotacaoDir(arv, pai);
                irmao = pai->esq;
            }
            if (irmao->dir->cor == 'p' && irmao->esq->cor == 'p') {
                irmao->cor = 'v';
                sucessor = pai;
                pai = pai->pai;
            }
            else {
                if (irmao->esq->cor == 'p') {
                    irmao->dir->cor = 'p';
                    irmao->cor = 'v';
                    rotacaoEsq(arv, irmao);
                    irmao = pai->esq;
                }
                irmao->cor = pai->cor;
                pai->cor = 'p';
                irmao->esq->cor = 'p';
                rotacaoDir(arv, pai);
                sucessor = getRaiz(arv);
                pai = NULL;
            }
        }
    }

    sucessor->cor = 'p';
}

void rotacaoEsq(rb* arv, no* noDesbalanceado) {
    no* filho = noDesbalanceado->dir;
    noDesbalanceado->dir = filho->esq;

    if (filho->esq != NULL) {
        filho->esq->pai = noDesbalanceado;
    }

    filho->esq = noDesbalanceado->pai;


    if (noDesbalanceado == noDesbalanceado->pai->esq) {
        noDesbalanceado->pai->esq = filho;
    }
    else {
        noDesbalanceado->pai->dir = filho;
    }


    filho->pai = noDesbalanceado->pai;
    filho->esq = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

void rotacaoDir(rb* arv, no* noDesbalanceado) {
    no* filho = noDesbalanceado->esq;
    noDesbalanceado->esq = filho->dir;

    if (filho->dir != NULL) {
        filho->dir->pai = noDesbalanceado;
    }

    filho->dir = noDesbalanceado->pai;

    if (noDesbalanceado == noDesbalanceado->pai->esq) {
        noDesbalanceado->pai->esq = filho;
    }
    else {
        noDesbalanceado->pai->dir = filho;
    }


    filho->pai = noDesbalanceado->pai;
    filho->dir = noDesbalanceado;
    noDesbalanceado->pai = filho;
}
