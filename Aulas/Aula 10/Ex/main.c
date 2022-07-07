#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main() {
    char nomeArquivo[100];
    scanf("%s", nomeArquivo);

    rb *novaArvore = criaArvore();

    carregaArvore(novaArvore, nomeArquivo);
    percorre(getRaiz(novaArvore));
    printf("\n");

    scanf("%s", nomeArquivo);

    removeElementos(novaArvore, nomeArquivo);
    percorre(getRaiz(novaArvore));
    printf("\n");

    free(novaArvore);
    return 0;
}
