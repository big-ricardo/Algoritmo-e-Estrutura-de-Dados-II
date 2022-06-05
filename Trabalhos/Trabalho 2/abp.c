#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"
#include "resultado.h"
#include "avl.h"

ArvBin* cria_ArvBin()
{
    ArvBin* nova = (ArvBin*)malloc(sizeof(ArvBin));
    (*nova) = NULL;
    return nova;
}

void imprime_em_ordem_ArvBin(ArvBin* raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esq != NULL)
        {
            imprime_em_ordem_ArvBin(&((*raiz)->esq));
        }
        printf("%d ", (*raiz)->chave);
        if ((*raiz)->dir != NULL)
        {
            imprime_em_ordem_ArvBin(&((*raiz)->dir));
        }
    }
}

int carregaArvoreABP(Registro* r, ArvBin* arv, FILE* arq) {
    int num;

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return -1;
    }

    while (fscanf(arq, "%d", &num) != EOF) {
        insere_ArvBin(arv, num);
    }

    fclose(arq);
    return 0;
}

int insere_ArvBin(ArvBin* raiz, int chave)
{
    if (raiz != NULL)
    {
        No* novo = malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->chave = chave;
        novo->altura = 0;
        No* aux = (*raiz);
        if ((*raiz) == NULL)
        {
            (*raiz) = novo;
            aux = (*raiz);
            novo->altura = 0;
            return 1;
        }

        while (aux->esq != NULL || aux->dir != NULL)
        {

            if (chave < aux->chave)
            {
                if (aux->esq == NULL)
                {
                    break;
                }
                aux = aux->esq;
            }
            else
            {
                if (aux->dir == NULL)
                {
                    break;
                }
                aux = aux->dir;
            }
        }

        if (chave < aux->chave)
        {
            aux->esq = novo;

            return 1;
        }
        else
        {
            aux->dir = novo;
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int busca_ArvBin(ArvBin* raiz, int chave)
{
    if (raiz != NULL)
    {
        struct No* atual = *raiz;
        while (atual != NULL)
        {
            if (chave == atual->chave)
            {
                return atual->chave;
            }
            if (chave > atual->chave)
            {
                atual = atual->dir;
            }
            else
            {
                atual = atual->esq;
            }
        }
    }

    return 0;
}

void libera_No(struct No* no)
{
    if (no != NULL)
    {
        libera_No(no->esq);
        libera_No(no->dir);
        free(no);
        no = NULL;
    }
}

void libera_ArvBin(ArvBin* raiz)
{
    if (raiz != NULL)
    {
        libera_No(*raiz);
        free(raiz);
    }
}