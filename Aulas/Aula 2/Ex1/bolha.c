#include "bolha.h"
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
*/

struct tReturn {
    void* vetor;
    int tamanho;
    int error;
};

tReturn* alocatReturn() {
    tReturn* retorno = (tReturn*)malloc(sizeof(tReturn));

    if (retorno == NULL) {
        return NULL;
    }

    retorno->vetor = NULL;
    retorno->tamanho = 0;
    retorno->error = 0;

    return retorno;
}

int* getVet(tReturn* rep) {
    return (int*)rep->vetor;
}

int getTam(tReturn* rep) {
    return rep->tamanho;
}

int getErro(tReturn* rep) {
    return rep->error;
}

void trataErro(int erro) {
    switch (erro)
    {
    case 1:
        printf("Erro: Arquivo nao encontrado\n");
        break;
    case 2:
        printf("Erro: Ler arquivo\n");
        break;
    case 3:
        printf("Erro: Nao foi possivel Alocar Memoria\n");
        break;
    }
}

tReturn* leArquivo(char nomeArquivo[]) {

    FILE* A = fopen(nomeArquivo, "r");
    tReturn* retorno = alocatReturn();

    if (retorno == NULL) {
        retorno->error = 3;
        return retorno;
    }

    if (A == NULL) {
        retorno->error = 1;
        return retorno;
    }
    int i = 0;
    int numero = 0;
    int tamanho = 0;

    if (fscanf(A, "%d", &tamanho) == 0) {
        retorno->error = 2;
        return retorno;
    }

    retorno->tamanho = tamanho;

    int* vetor = (int*)malloc(sizeof(int) * tamanho);

    if (vetor == NULL) {
        retorno->error = 3;
        return retorno;
    }

    while (fscanf(A, "%d", &numero) != EOF) {
        vetor[i] = numero;
        i++;
    }

    if (i != tamanho) {
        retorno->error = 2;
        return retorno;
    }

    retorno->vetor = vetor;
    retorno->tamanho = i;

    fclose(A);
    return retorno;
}

void bolha(int* vet, int tam) {
    int aux;
    for (int i = 0; i < tam; i++) {
        for (int j = 1; j < tam; j++) {
            if (vet[j] < vet[j - 1]) {
                aux = vet[j - 1];
                vet[j - 1] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

void bolhaInteligente(int* vet, int tam) {
    int aux;
    bool troca = true;
    for (int i = 0; (i < tam && troca); i++) {
        troca = false;
        for (int j = 1; j < tam; j++) {
            if (vet[j] < vet[j - 1]) {
                troca = true;
                aux = vet[j - 1];
                vet[j - 1] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

void imprimeVet(int* vet, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d\n", vet[i]);
    }
}