#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#define true 1
#define false 0

#define RESULTADO_TXT "./resutados/r"

typedef struct {
    double tempo;
    int trocas;
    int copias;
    char tipo;
    int qtd;
    int caso;
    char* metodo;
} Registro;


int bubbleSort(int* vetor, int tam) {
    int i, j, aux, trocas = 0;
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                trocas++;
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }

    return trocas;
}

bool computarOrdenacaoBubbleSort(Registro* r, int* vetor, int tamanho) {

    clock_t inicio, fim;
    inicio = clock();

    r->trocas = bubbleSort(vetor, tamanho);

    fim = clock();
    r->tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    return true;
}

bool realizarOrdenacao(char tipo, char metodo, int tam, int casos_teste) {

    FILE* salvarRegistro(Registro);

    Registro r;
    r.tipo = tipo;
    r.qtd = tam;

    for (int j = 0; j < casos_teste; j++) {
        int* dados = lerDados(tipo, tam, j);

        r.trocas = 0;
        r.copias = 0;
        r.tempo = 0;
        r.caso = j;

        if (dados == NULL) {
            free(dados);
            return false;
        }

        switch (metodo) {
        case 'b':
            r.metodo = "bubbleSort";
            computarOrdenacaoBubbleSort(&r, dados, tam);
            break;
        case 'i':
            break;
        }

        free(dados);

        if (!salvarRegistro(r)) {
            printf("Erro ao escrever resultado\n");
            return false;
        }
    }

    return true;
}

bool criarArquivoResultado(char* metodo) {
    char path[40] = "";

    sprintf(path, "%s_%s.csv", RESULTADO_TXT, metodo);

    FILE* arquivo = fopen(path, "w+");
    if (arquivo == NULL)
        return false;

    if (fprintf(arquivo, "tipo,qtd,caso,tempo,trocas,copias\n") < 0) {
        printf("Erro ao criar arquivo de resultado\n");
        return false;
    }

    fclose(arquivo);
    return true;
}

FILE* salvarRegistro(Registro r) {
    char path[40] = "";

    sprintf(path, "%s_%s.csv", RESULTADO_TXT, r.metodo);

    FILE* arquivo = fopen(path, "a+");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de resultado %s.\n", path);
        return NULL;
    }

    if (fprintf(arquivo, "%c,%d,%d,%lf,%d,%d\n", r.tipo, r.qtd, r.caso, r.tempo, r.trocas, r.copias) < 0) {
        printf("Erro ao salvar registro de resultado %s.\n", path);
        return NULL;
    }

    fclose(arquivo);

    return arquivo;
}

bool zerarArquivosResultados() {

    if (!criarArquivoResultado("bubbleSort"))
        return false;

    return true;
}
