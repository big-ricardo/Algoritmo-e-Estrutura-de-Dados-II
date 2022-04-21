#include<stdlib.h>
#include<stdio.h>
#include "selecaoInsercao.h"
#define true 1
#define false 0

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/


//Esta função gera 'qtd' números aleatórios e os escreve no arquivo 'nomeArquivo'
//Os numeros devem variar entre 0 e 1000.
//A função retorna 0 se funcionou corretamente. Retorna 1 se houve algum erro no processo.
//Pesquisem pelas funções rand() e srand().
int geraAleatorios(char* nomeArquivo, int qtd) {

    srand(qtd);

    FILE* arquivo = fopen(nomeArquivo, "w+");

    if (arquivo == NULL) {
        fclose(arquivo);
        return false;
    }

    for (int i = 0; i < qtd; i++) {
        int numero = rand() % 1000;
        if (!fprintf(arquivo, "%d\n", numero)) {
            fclose(arquivo);
            return false;
        }
    }

    fclose(arquivo);
    return true;
}

//Esta função lê 'qtd' dados do arquivo 'nomeArquivo' e os insere em um vetor de inteiros
//A função retorna NULL caso haja algum erro no processo.
int* leArquivo(char* nomeArquivo, int qtd) {
    int* vetor = (int*)malloc(qtd * sizeof(int));

    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        free(vetor);
        return NULL;
    }

    for (int i = 0; i < qtd; i++) {
        if (fscanf(arquivo, "%d", &vetor[i]) != 1) {
            free(vetor);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return (int*)vetor;
}

//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem crescente) utilizando o método seleção
void selecao(int* vet, int tam) {
    int aux, menor;
    for (int i = 0; i < tam - 1; i++) {
        menor = i;
        for (int j = i + 1; j < tam; j++) {
            if (vet[j] < vet[menor]) {
                menor = j;
            }
        }
        if (i != menor) {
            aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
        }
    }
}

//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem decrescente) utilizando o método seleção
void selecaoDecrescente(int* vet, int tam) {
    int aux, maior;
    for (int i = 0; i < tam - 1; i++) {
        maior = i;
        for (int j = i + 1; j < tam; j++) {
            if (vet[j] > vet[maior]) {
                maior = j;
            }
        }
        if (i != maior) {
            aux = vet[i];
            vet[i] = vet[maior];
            vet[maior] = aux;
        }
    }
}

//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena utilizando o método dual seleção
void dualSelecao(int* vet, int tam) {
    for (int i = 0, j = tam - 1; i < j; i++, j--) {
        int menor = vet[i], maior = vet[i];
        int menor_i = i, maior_i = i;

        for (int k = i; k <= j; k++) {
            if (vet[k] > maior) {
                maior = vet[k];
                maior_i = k;
            }
            else if (vet[k] < menor) {
                menor = vet[k];
                menor_i = k;
            }
        }

        if (menor_i != i) {
            int aux = vet[i];
            vet[i] = vet[menor_i];
            vet[menor_i] = aux;
        }

        if (vet[menor_i] == maior) {
            int aux = vet[j];
            vet[j] = vet[menor_i];
            vet[menor_i] = aux;
        }
        else {
            int aux = vet[j];
            vet[j] = vet[maior_i];
            vet[maior_i] = aux;
        }
    }

    return;
}

//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena utilizando o método insercao
void insercao(int* vet, int tam) {
    int aux;

    for (int i = 1; i < tam; i++) {
        aux = vet[i];
        int j = i - 1;
        for (; (j >= 0 && aux < vet[j]); j--) {
            vet[j + 1] = vet[j];
        }
        vet[j + 1] = aux;
    }

    return;
}

//Esta função recebe um vetor e o imprime na tela
//A impressão é em linha -> printf("%d ", vet[i]);
//Antes de encerrar, a função imprime uma linha em branco
void imprimeVet(int* vet, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");

    return;
}