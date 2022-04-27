#include <stdio.h>
#include <stdlib.h>
#include "mergeQuick.h"
#define true 1
#define false 0
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

int main(void) {

    char arquivo[20] = "arquivo.txt";
    int qtd = 11;
    int* vetor = NULL;

    geraAleatorios(arquivo, qtd);
    vetor = leArquivo(arquivo, qtd);
    imprimeVet(vetor, qtd);

    mergeSort(vetor, 0, qtd - 1);
    imprimeVet(vetor, qtd);

    vetor = leArquivo(arquivo, qtd);
    quickSort(vetor, 0, qtd - 1);
    imprimeVet(vetor, qtd);

    return 0;

}