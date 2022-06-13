#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/*
  Luis Ricardo Albano Santos - 2021031844
  Guilherme Schimidt - 2020011524
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

    if (arv == NULL) {
        printf("Erro ao alocar memoria para a arvore.\n");
        return NULL;
    }

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

    atualizaFB_Insercao(arv, novoNo);

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
int removeNo(avl* arv, int chave) {
    no* atual = getRaiz(arv);
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
        printf("Elemento nao encontrado\n");
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

    int auxChave = atual->chave;

    if (atual->pai != arv->sentinela) {
        atualizaFB_Remocao(arv, atual->pai, auxChave);
    }

    free(atual);
    arv->numElementos--;

    return 0;
}

//Percorrimento em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(no* raiz) {
    if (raiz != NULL) {
        printf("%d: %d\t", raiz->chave, raiz->fb);
        // imprimeNo(raiz);
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
        printf("\n########################\n");
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
        if (atual->pai != NULL && atual->pai->pai != NULL) {
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

void atualizaFB_Insercao(avl* arv, no* novoNo) {
    no* aux = novoNo;

    do {
        if (aux->pai->chave <= aux->chave) {
            aux->pai->fb++;
        }
        else {
            aux->pai->fb--;
        }
        aux = aux->pai;

    } while (aux->pai != arv->sentinela && aux->fb != 0 && (aux->fb != 2 && aux->fb != -2));

    if (aux->fb == -2 || aux->fb == 2) {
        balanceamento(arv, aux);
    }

}

void atualizaFB_Remocao(avl* arv, no* pai, int chave) {
    no* aux = pai;

    if (aux->chave <= chave) {
        aux->fb--;
    }
    else {
        aux->fb++;
    }

    while (aux != arv->sentinela && aux->fb == 0) {
        aux = aux->pai;
        if (aux->chave <= chave) {
            aux->fb--;
        }
        else {
            aux->fb++;
        }
    }

    if (aux->fb == -2 || aux->fb == 2) {
        balanceamento(arv, aux);
        aux = aux->pai;
        if (aux != arv->sentinela && aux->fb == 0) {
            atualizaFB_Remocao(arv, aux->pai, chave);
        }
    }
}

void balanceamento(avl* arv, no* noDesbalanceado) {

    no* filho = NULL;

    if (noDesbalanceado->fb == 2) {
        filho = noDesbalanceado->dir;
        if (filho->fb == -1) {
            no* neto = filho->esq;
            rotacaoDir(arv, filho);
            rotacaoEsq(arv, noDesbalanceado);
            if (neto->fb == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if (neto->fb == 1) {
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }
            else if (neto->fb == -1) {
                noDesbalanceado->fb = 0;
                filho->fb = 1;
            }
            neto->fb = 0;

        }
        else if (filho->fb == 0) {
            rotacaoEsq(arv, noDesbalanceado);
            noDesbalanceado->fb = 1;
            filho->fb = -1;
        }
        else {
            rotacaoEsq(arv, noDesbalanceado);
            if (filho->fb == 1) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
        }
    }
    else {
        filho = noDesbalanceado->esq;
        if (filho->fb == 1) {
            no* neto = filho->dir;
            rotacaoEsq(arv, filho);
            rotacaoDir(arv, noDesbalanceado);
            if (neto->fb == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if (neto->fb == 1) {
                noDesbalanceado->fb = 0;
                filho->fb = -1;
            }
            else {
                noDesbalanceado->fb = 1;
                filho->fb = 0;
            }
            neto->fb = 0;
        }
        else if (filho->fb == 0) {
            rotacaoDir(arv, noDesbalanceado);
            noDesbalanceado->fb = -1;
            filho->fb = 1;
        }
        else {
            rotacaoDir(arv, noDesbalanceado);
            if (filho->fb == -1) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
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

void rotacaoDir(avl* arv, no* noDesbalanceado) {
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
