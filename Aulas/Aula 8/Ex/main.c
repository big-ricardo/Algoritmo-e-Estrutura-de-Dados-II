#include <stdio.h>
#include "abp.h"

int main() {
    int res, chave;
    char nomeArquivo[100];
    abp* novaArvore = criaArvore();

    scanf("%s", nomeArquivo);

    carregaArvore(novaArvore, nomeArquivo);
    percorre(getRaiz(novaArvore));

    scanf("%d", &chave);

    res = removeNo(novaArvore, chave);

    percorre(getRaiz(novaArvore));
    if (res == 0)
        printf("\n Elemento %d removido com sucesso \n", chave);
    else
    {
        if (res == -1)
            printf("\nÁrvore Vazia");
        else
            printf("\nElemento %d não encontrado na arvore \n", chave);
    }

    res = removeNo(novaArvore, chave);
    if (res == 0)
        printf("\n Elemento %d removido com sucesso \n", chave);
    else
    {
        if (res == -1)
            printf("\nÁrvore Vazia");
        else
            printf("\nElemento %d não encontrado na arvore \n", chave);
    }

    scanf("%d", &chave);

    percorre(getRaiz(novaArvore));

    no* aux = recuperaNo(novaArvore, chave);
    if (aux == NULL)
        printf("\nElemento %d não encontrado na arvore \n", chave);
    else
        imprimeNo(aux);

    scanf("%d", &chave);

    aux = recuperaNo(novaArvore, chave);
    if (aux == NULL)
        printf("\nElemento %d não encontrado na arvore \n", chave);
    else
        imprimeNo(aux);

    printf("\nA arvore possui %d elementos\n", getNumElementos(novaArvore));

    return 0;
}
