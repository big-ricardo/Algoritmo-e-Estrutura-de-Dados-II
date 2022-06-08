#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main() {
    int chave;
    char nomeArquivo[100]; // = "entrada.txt";
    avl* novaArvore = criaArvore();

    scanf("%s", nomeArquivo);

    carregaArvore(novaArvore, nomeArquivo);
    percorre(getRaiz(novaArvore));
    printf("\nAltura da arvore: %d.\n", getAltura(getRaiz(novaArvore)));

    scanf("%d", &chave);
    removeNo(novaArvore, chave);
    percorre(getRaiz(novaArvore));

    scanf("%d", &chave);
    removeNo(novaArvore, chave);
    percorre(getRaiz(novaArvore));

    scanf("%d", &chave);
    removeNo(novaArvore, chave);
    percorre(getRaiz(novaArvore));

    printf("\n");

    percorre(getRaiz(novaArvore));
    printf("\nAltura da arvore: %d.\n", getAltura(getRaiz(novaArvore)));

    free(novaArvore);
}
