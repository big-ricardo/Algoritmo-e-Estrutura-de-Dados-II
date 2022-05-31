#include <stdio.h>
#include "avl.h"

int main() {
    char nomeArquivo[100] = "as";
    avl* novaArvore = criaArvore();

    // scanf("%s", nomeArquivo);

    carregaArvore(novaArvore, nomeArquivo);
    // percorre(getRaiz(novaArvore));

    removeNo(novaArvore, 25);
    percorre(getRaiz(novaArvore));


    return 0;
}
