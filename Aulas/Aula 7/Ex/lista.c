#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/*
  Diovana Tavares dos Reis - 2021016991
  Luis Ricardo Albano Santos - 2021031844
*/

struct no {
    char palavra[30];
    struct no* prox;
};

struct lista {
    struct no* inicio;
    int tam;
};


//Aloca e inicializa uma lista
lista* criaLista() {
    lista* l = (lista*)malloc(sizeof(lista));
    if (l == NULL) {
        printf("Erro ao alocar memoria\n");
        return NULL;
    }

    l->inicio = NULL;
    l->tam = 0;
    return l;
}

//Insere uma nova palavra na lista. Ou seja, aloca um nó, inicializa e o insere na lista.
//A insersão é sempre no começo da lista.
//Retorna 1 caso ocorra erro na inserção e 0 caso contrário.
int insereLista(lista* l, char* palavra) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    strcpy(novo->palavra, palavra);
    novo->prox = l->inicio;
    l->inicio = novo;
    l->tam++;

    return 0;
}

//Retorna a lista de uma determinada posição da tabela hash
lista* getLista(lista** vet, int pos) {
    return vet[pos];
}

int getTamLista(lista* l) {
    return l->tam;
}
//Retorna o tam de uma determinada lista

//Verifica se uma palavra está presente ou não em uma lista
//Se a palavra estiver presente, retorna 1. Caso contrário, retorna 0;
int buscaLista(lista* l, char* palavra) {
    no* aux = l->inicio;
    while (aux != NULL) {
        if (strcmp(aux->palavra, palavra) == 0) {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

//Remove uma palavra da lista
void removeLista(lista* l, char* palavra) {
    struct no* aux = l->inicio;
    struct no* ant = NULL;

    while (aux != NULL) {
        if (strcmp(aux->palavra, palavra) == 0) {
            if (ant == NULL) {
                l->inicio = aux->prox;
            }
            else {
                ant->prox = aux->prox;
            }
            free(aux);
            l->tam--;
            aux = NULL;
        }
        else {
            ant = aux;
            aux = aux->prox;
        }
    }
}

//Imprime as palavras de uma lista => printf("%s\n", noAux->palavra);
//Se a lista estiver vazia => printf("Lista Vazia\n");
void imprimeLista(lista* l) {
    struct no* aux = l->inicio;

    if (l->inicio == NULL) {
        printf("Lista Vazia\n");
    }
    else {
        while (aux != NULL) {
            printf("%s\n", aux->palavra);
            aux = aux->prox;
        }
    }
}