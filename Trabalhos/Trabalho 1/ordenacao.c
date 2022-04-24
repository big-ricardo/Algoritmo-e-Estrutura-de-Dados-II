#include <stdio.h>
#include <stdlib.h>

#include "resultado.h"

#define true 1
#define false 0

#define ORDENACAO_TXT "./auditoria/o"

typedef int bool;

// Algoritmo de ordenação selectionSort
void selecao(Registro* r, int* vet, int tam) {
    int aux, menor;
    unsigned long int comparacoes = 0, copias = 0;

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
            copias += 3;
        }
    }

    r->comparacoes = comparacoes;
    r->copias = copias;

    return;
}

// Algoritmo responsavel por particionar o vetor para o quick sort
int  particiona(Registro* r, int* vet, int inicio, int fim) {
    int pivo = vet[inicio];
    int pos = inicio;
    int aux;
    int comparacoes = 0, copias = 0;

    for (int i = inicio + 1; i <= fim; i++) {
        comparacoes++;
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

// Algoritmo de ordenação QuickSort
void quickSort(Registro* r, int* vet, int inicio, int fim) {
    int pivo;

    if (inicio < fim) {
        pivo = particiona(r, vet, inicio, fim);
        quickSort(r, vet, inicio, pivo - 1);
        quickSort(r, vet, pivo + 1, fim);
    }

    return;
}

// Algortimo de ordenacao apresentado no 
void mobileSort(Registro* r, int* vet, int tam) {
    unsigned long int copias = 0, comparacoes = 0;

    for (int i = 0; i < tam; i++) {
        int maior = i;
        int menor = i;

        for (int j = i + 1; j < tam; j++) {
            comparacoes++;
            if (vet[j] < vet[menor]) {
                menor = j;
            }
            else {
                comparacoes++;
                if (vet[j] > vet[maior]) {
                    maior = j;
                }
            }
        }

        if (menor != i) {
            int aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
            copias += 3;
        }

        if (maior != tam - 1) {
            int aux = vet[tam - 1];
            vet[tam - 1] = vet[maior];
            vet[maior] = aux;
            copias += 3;
        }

        comparacoes += 2;

        tam--;
    }

    r->comparacoes = comparacoes;
    r->copias = copias;
}

bool criarArquivoOrdenacao(char* metodo) {
    char path[40] = "";

    sprintf(path, "%s_%s.txt", ORDENACAO_TXT, metodo);

    FILE* arquivo = fopen(path, "w+");
    if (arquivo == NULL)
        return false;

    if (fprintf(arquivo, "\n") < 0) {
        printf("Erro ao criar arquivo de ordenacao %s\n", path);
        return false;
    }

    fclose(arquivo);
    return true;
}

bool salvarOrdenacao(Registro r, int* vet, int tam) {
    char path[40] = "";

    sprintf(path, "%s_%s.txt", ORDENACAO_TXT, r.metodo);

    FILE* arquivo = fopen(path, "a+");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de resultado %s.\n", path);
        return false;
    }

    for (int i = 0; i < tam; i++) {
        if (fprintf(arquivo, "%d ", vet[i]) < 0) {
            printf("Erro ao salvar registro no arquivo de ordenacao %s.\n", path);
            return false;
        }
    }

    if (fprintf(arquivo, "\n ---------\n") < 0) {
        printf("Erro ao salvar registro no arquivo de ordenacao %s.\n", path);
        return false;
    }

    fclose(arquivo);

    return true;
}