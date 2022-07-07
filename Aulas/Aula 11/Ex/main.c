#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main() {

    char nomeArquivoEntrada[30] = "ent";
    char nomeArquivoRemove[30] = "as";
    int ordem;

    // scanf("%s", nomeArquivoEntrada);
    // scanf("%s", nomeArquivoRemove);
    // scanf("%d", &ordem);

    btree* b = criaArvore(4);
    if (b == NULL)
    {
        printf("A ordem deve ser par\n");
        return 1;
    }

    manipulaBTree(b, nomeArquivoEntrada, 'i');

    // imprimeArvore((retornaRaiz(b)), 0);
    printf("\n");

    manipulaBTree(b, nomeArquivoRemove, 'r');

    // imprimeArvore((retornaRaiz(b)), 0);

    printf("\n");

    free(b);

    return 0;
}
