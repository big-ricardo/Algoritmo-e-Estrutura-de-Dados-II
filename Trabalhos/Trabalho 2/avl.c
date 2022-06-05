#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h"
#include "resultado.h"

ArvAVL* cria_ArvAVL()
{
    ArvAVL* raiz = (ArvAVL*)malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_ArvAVL(Registro* r, ArvAVL* raiz)
{
    if (raiz != NULL)
    {
        libera_No(*raiz); // libera cada nó
        free(raiz);       // libera a raiz
    }
}

int carregaArvoreAvl(Registro* r, ArvAVL* arv, FILE* arq) {
    int num;

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return -1;
    }

    while (fscanf(arq, "%d", &num) != EOF) {
        insere_ArvAVL(r, arv, num);
    }

    fclose(arq);
    return 0;
}

int altura_No(struct No* no)
{
    if (no == NULL)
    {
        return -1;
    }
    else
    {
        return no->altura;
    }
}

int fator_balanceamento_No(struct No* no)
{
    return labs(altura_No(no->esq) - altura_No(no->dir));
}

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

void imprime_pre_ordem_ArvAVL(ArvAVL* raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        printf("%d ", (*raiz)->chave);
        imprime_pre_ordem_ArvAVL(&((*raiz)->esq));
        imprime_pre_ordem_ArvAVL(&((*raiz)->dir));
    }
}

void imprime_em_ordem_ArvAVL(ArvAVL* raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        imprime_em_ordem_ArvAVL(&((*raiz)->esq));
        printf("%d ", (*raiz)->chave);
        imprime_em_ordem_ArvAVL(&((*raiz)->dir));
    }
}

int busca_ArvAVL(ArvAVL* raiz, int chave)
{
    if (raiz == NULL)
    {
        return 0;
    }
    struct No* atual = *raiz;
    while (atual != NULL)
    {
        if (chave == atual->chave)
        {
            return atual->chave;
        }
        if (chave >= atual->chave)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->esq;
        }
    }
    return 0;
}

/* LR = Left rotation
 * RR = Right rotation
 * LRR = Left-right rotation
 * RLR = Right-left rotation
 */

void rotacao_LR(ArvAVL* A)
{
    struct No* B;

    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_No((*A)->esq), altura_No((*A)->dir)) + 1;
    B->altura = maior(altura_No(B->esq), (*A)->altura) + 1;
    *A = B;
}

void rotacao_RR(ArvAVL* A)
{
    struct No* B;

    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_No((*A)->esq), altura_No((*A)->dir)) + 1;
    B->altura = maior(altura_No(B->dir), (*A)->altura) + 1;
    (*A) = B;
}

void rotacao_LRR(ArvAVL* A)
{
    rotacao_RR(&(*A)->esq);
    rotacao_LR(A);
}

void rotacao_RLR(ArvAVL* A)
{
    rotacao_LR(&(*A)->dir);
    rotacao_RR(A);
}

int insere_ArvAVL(Registro* r, ArvAVL* raiz, int chave)
{
    int res;
    if (*raiz == NULL)
    { //Arvore vazia ou no folha
        struct No* novo;
        novo = (struct No*)malloc(sizeof(struct No));
        if (novo == NULL)
            return 0;

        novo->chave = chave;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct No* atual = *raiz;
    if (chave < atual->chave)
    {
        if ((res = insere_ArvAVL(r, &(atual->esq), chave)) == 1)
        {
            if (fator_balanceamento_No(atual) >= 2)
            {
                if (chave < atual->esq->chave)
                {
                    r->rot_carregar++;
                    rotacao_LR(raiz);
                }
                else
                {
                    r->rot_carregar += 2;
                    rotacao_LRR(raiz);
                }
            }
        }
    }
    else
    {

        if ((res = insere_ArvAVL(r, &(atual->dir), chave)) == 1)
        {
            if (fator_balanceamento_No(atual) >= 2)
            {
                if (chave >= (*raiz)->dir->chave)
                {
                    r->rot_carregar++;
                    rotacao_RR(raiz);
                }
                else
                {
                    r->rot_carregar += 2;
                    rotacao_RLR(raiz);
                }
            }
        }
    }

    atual->altura = maior(altura_No(atual->esq), altura_No(atual->dir)) + 1;

    return res;
}