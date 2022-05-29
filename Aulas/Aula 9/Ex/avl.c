#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/*
  Diovana Tavares dos Reis - 2021016991
  Luis Ricardo Albano Santos - 2021031844
*/

struct no {
    int chave;
    int fb;
    no* esq;
    no* dir;
    no* pai;
};

struct arvore {
    no* sentinela;
    int numElementos;
};

avl* criaArvore() {
    avl* arv = (avl*)malloc(sizeof(avl));
    arv->sentinela = (no*)malloc(sizeof(no));
    arv->sentinela->chave = -1000;
    arv->sentinela->esq = NULL;
    arv->sentinela->dir = NULL;
    arv->sentinela->pai = NULL;
    arv->numElementos = 0;
    return arv;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no* getRaiz(avl* arv) {
    return arv->sentinela->dir;
}

//Popula uma árvore binária de pesquisa a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(avl* arv, char* nomeArquivo) {
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

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(avl* arv, int chave) {
    no* novoNo = (no*)malloc(sizeof(no));
    no* atual = getRaiz(arv);
    no* pai = NULL;

    novoNo->chave = chave;
    novoNo->fb = 0;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->pai = NULL;

    while (atual != NULL) {
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

    atualizaFbInsercao(arv, novoNo);

    return 0;
}

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(avl* arv, int chave) {
    no* atual = arv->sentinela;
    no* filho = NULL;
    no* aux = NULL;

    while (atual != NULL && atual->chave != chave) {
        if (chave < atual->chave) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    if (atual == NULL) {
        return -2;
    }

    if (atual->esq != NULL && atual->dir != NULL) {
        aux = atual->dir;
        while (aux->esq != NULL) {
            aux = aux->esq;
        }
        atual->chave = aux->chave;
        atual = aux;
    }

    if (atual->esq != NULL) {
        filho = atual->esq;
    }
    else {
        filho = atual->dir;
    }

    if (filho != NULL) {
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
    }

    free(atual);
    arv->numElementos--;

    return 0;
}

//Percorrimento em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(no* raiz) {
    if (raiz != NULL) {
        // printf("%d\t", raiz->chave);
        imprimeNo(raiz);
        percorre(raiz->esq);
        percorre(raiz->dir);
    }
}

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no* recuperaNo(avl* arv, int chave) {
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
void imprimeNo(no* atual) {
    if (atual != NULL) {
        printf("\n\n########################\n");
        printf("Chave : %d\n", atual->chave);
        printf("Fb: %d\n", atual->fb);
        if (atual->esq != NULL) {
            printf("Filho Esq : %d\n", atual->esq->chave);
        }
        else {
            printf("Filho Esq : NULO\n");
        }
        if (atual->dir != NULL) {
            printf("Filho Dir : %d\n", atual->dir->chave);
        }
        else {
            printf("Filho Dir : NULO\n");
        }
        if (atual->pai->chave != -1000) {
            printf("Pai : %d\n", atual->pai->chave);
        }
        else {
            printf("Pai : Sentinela\n");
        }
    }
}

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(avl* arv) {
    return arv->numElementos;
}

void atualizaFbInsercao(avl* arv, no* novoNo) {
    no* aux = novoNo;

    do {
        if (aux->pai != arv->sentinela) {
            if (aux->pai->chave < aux->chave) {
                aux->pai->fb++;
            }
            else {
                aux->pai->fb--;
            }
            aux = aux->pai;
        }
    } while (aux->pai != arv->sentinela && aux->fb != 0);
    // imprimeNo(aux);
    if (aux->fb == -2 || aux->fb == 2) {
        balanceamentoInsercao(arv, aux);
    }

}

void balanceamentoInsercao(avl* arv, no* noDesbalanceado) {

    no* filho = NULL;

    if (noDesbalanceado->fb == 2) {
        filho = noDesbalanceado->dir;
        if (filho->fb == -1) {
            int fbNeto = filho->esq->fb;
            rotacaoDir(arv, filho);
            rotacaoEsq(arv, noDesbalanceado);
            if (fbNeto == -1) {
                atualizaFbInsercao(arv, noDesbalanceado->dir);
            }
            else {
                atualizaFbInsercao(arv, noDesbalanceado->esq);
                atualizaFbInsercao(arv, filho->dir);
            }
        }
        else {
            rotacaoEsq(arv, noDesbalanceado);
            atualizaFbInsercao(arv, noDesbalanceado);
            if (filho->fb == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else {
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }
        }
    }
    else {
        filho = noDesbalanceado->esq;
        if (filho->fb == 1) {
            int fbNeto = filho->dir->fb;
            rotacaoEsq(arv, filho);
            rotacaoDir(arv, noDesbalanceado);
            if (fbNeto == -1) {
                atualizaFbInsercao(arv, noDesbalanceado->dir);
            }
            else {
                atualizaFbInsercao(arv, noDesbalanceado->esq);
            }
        }
        else {
            rotacaoDir(arv, noDesbalanceado);
            atualizaFbInsercao(arv, noDesbalanceado->pai);
            if (filho->fb == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else {
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }

        }
    }
}

void rotacaoEsq(avl* arv, no* noDesbalanceado) {
    no* filho = noDesbalanceado->dir;
    noDesbalanceado->dir = filho->esq;

    if (filho->esq != NULL) {
        filho->esq->pai = noDesbalanceado;
    }

    filho->esq = noDesbalanceado->pai;

    if (noDesbalanceado->pai == NULL) {
        arv->sentinela = filho;
    }
    else {
        if (noDesbalanceado == noDesbalanceado->pai->esq) {
            noDesbalanceado->pai->esq = filho;
        }
        else {
            noDesbalanceado->pai->dir = filho;
        }
    }

    filho->esq = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

void rotacaoDir(avl* arv, no* noDesbalanceado) {
    no* filho = noDesbalanceado->esq;
    noDesbalanceado->esq = filho->dir;

    if (filho->dir != NULL) {
        filho->dir->pai = noDesbalanceado;
    }

    filho->dir = noDesbalanceado->pai;

    if (noDesbalanceado->pai == NULL) {
        arv->sentinela = filho;
    }
    else {
        if (noDesbalanceado == noDesbalanceado->pai->esq) {
            noDesbalanceado->pai->esq = filho;
        }
        else {
            noDesbalanceado->pai->dir = filho;
        }
    }

    filho->dir = noDesbalanceado;
    noDesbalanceado->pai = filho;
}
