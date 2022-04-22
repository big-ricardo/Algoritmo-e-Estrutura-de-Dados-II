#include "resultado.h"

void selecao(Registro* r, int* vet, int tam) {
    int aux, menor;
    int comparacoes = 0, copias = 0;

    for (int i = 0; i < tam - 1; i++) {
        menor = i;
        for (int j = i + 1; j < tam; j++) {
            if (vet[j] < vet[menor]) {
                menor = j;
            }
        }
        comparacoes += tam - i;

        if (vet[menor] < vet[i]) {
            aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
        }
    }

    r->comparacoes = comparacoes;
    r->copias = copias;

    return;
}

int  particiona(Registro* r, int* vet, int inicio, int fim) {
    int pivo = vet[inicio];
    int pos = inicio;
    int aux, comparacoes = 0, copias = 0;

    for (int i = inicio + 1; i <= fim; i++) {
        if (vet[i] < pivo) {
            pos++;
            if (pos != i) {
                aux = vet[pos];
                vet[pos] = vet[i];
                vet[i] = aux;
                copias += 3;
            }
        }
    }

    aux = vet[inicio];
    vet[inicio] = vet[pos];
    vet[pos] = aux;

    copias += 3;

    r->comparacoes += comparacoes;
    r->copias += copias;

    return pos;
}

void quickSort(Registro* r, int* vet, int inicio, int fim) {
    int pivo;
    int comparacoes = 0, copias = 0;

    if (inicio < fim) {
        pivo = particiona(r, vet, inicio, fim);
        quickSort(r, vet, inicio, pivo - 1);
        quickSort(r, vet, pivo + 1, fim);
    }

    r->comparacoes += comparacoes;
    r->copias += copias;

    return;
}