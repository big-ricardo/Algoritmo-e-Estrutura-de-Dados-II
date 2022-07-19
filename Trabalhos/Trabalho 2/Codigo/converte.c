#include <stdio.h>
#include <stdlib.h>
#include "converte.h"
#include "btree.h"
#include "rb.h"

/*
  Luis Ricardo Albano Santos - 2021031844
  Matheus Martins Batista 2019005687
*/

// Função que chama as função recursiva para converter a arvore 2-3-4 em uma arvore rubro-negra
rb* converte(btree* bt) {

    void converteNos(noBt * btAtual, noRb * rbAtual, rb * rb);  //função recursiva para converter a arvore 2-3-4 em uma arvore rubro-negra

    rb* rb = criaArvoreRb();    //cria arvore rubro-negra
    noBt* btAtual = retornaRaiz(bt);    //ponteiro para o no raiz da arvore 2-3-4

    converteNos(btAtual, NULL, rb);  //chama a função recursiva para converter a arvore 2-3-4 em uma arvore rubro-negra

    return rb;  //retorna a arvore rubro-negra
}

//Converte os nós da BTree recursivamente
void converteNos(noBt* btAtual, noRb* rbAtual, rb* rb) {
    if (btAtual == NULL) return;    //se o no atual for nulo, retorna

    if (btAtual->ocupacao == 0) {   //se o no atual nao tiver elementos, retorna
        printf("Vazio");
        return;
    }


    noRb* novoNo = (noRb*)malloc(sizeof(noRb)); //aloca um novo no da arvore rubro-negra

    if (btAtual->ocupacao == 1) { //nó de ordem 2
        novoNo->chave = btAtual->chaves[0]; //copia a chave do no atual para o novo no
        novoNo->cor = 'p';  //define a cor do novo no como preto

        if (btAtual->folha == 1) {  //se o no atual for folha, define filhos do novo no como folha
            novoNo->dir = getNULL(rb);
            novoNo->esq = getNULL(rb);
        }

        rb->numElementos++; //incrementa o numero de elementos da arvore rubro-negra
    }
    else if (btAtual->ocupacao == 2) { //nó de ordem 3
        //primeiro elemento vira o pai e segundo o filho
        novoNo->chave = btAtual->chaves[0]; //copia a chave do no atual para o novo no
        novoNo->cor = 'p';  //define a cor do novo no como preto

        noRb* novoFilho = (noRb*)malloc(sizeof(noRb));  //aloca um novo no da arvore rubro-negra
        novoFilho->chave = btAtual->chaves[1];  //copia a chave do no atual para o novo no
        novoFilho->cor = 'v';   //define a cor do novo no como vermelho

        //se o no atual for folha, define filho a esquerda do novo no como folha e filhos do no filho a direta como folha
        if (btAtual->folha == 1) {
            novoNo->esq = getNULL(rb);
            novoFilho->dir = getNULL(rb);
            novoFilho->esq = getNULL(rb);
        }

        novoFilho->pai = novoNo;    //define o pai do novo no como o novo no
        novoNo->dir = novoFilho;    //define o filho a direta do novo no como o novo no
        rb->numElementos += 2;   //incrementa o numero de elementos da arvore rubro-negra
    }
    else { //nó de ordem 4
        //elemento do meio vira o pai e os demais filhos
        novoNo->chave = btAtual->chaves[1]; //copia a chave do no atual para o novo no
        novoNo->cor = 'p';  //define a cor do novo no como preto

        noRb* novoDir = (noRb*)malloc(sizeof(noRb));    //aloca um novo no da arvore rubro-negra
        novoDir->chave = btAtual->chaves[2];    //copia a chave do no atual para o novo no
        novoDir->cor = 'v';  //define a cor do novo no como vermelho

        noRb* novoEsq = (noRb*)malloc(sizeof(noRb));    //aloca um novo no da arvore rubro-negra
        novoEsq->chave = btAtual->chaves[0];    //copia a chave do no atual para o novo no
        novoEsq->cor = 'v'; //define a cor do novo no como vermelho

        //se o no atual for folha, define filhos dos filhos novo no como folha
        if (btAtual->folha == 1) {
            novoEsq->dir = getNULL(rb);
            novoEsq->esq = getNULL(rb);
            novoDir->dir = getNULL(rb);
            novoDir->esq = getNULL(rb);
        }

        novoDir->pai = novoNo;  //define o pai do novo no como o novo no
        novoEsq->pai = novoNo;
        novoNo->esq = novoEsq;  //define o filho a esquerda do novo no como o novo no
        novoNo->dir = novoDir;  //define o filho a direta do novo no como o novo no

        rb->numElementos += 3;  //incrementa o numero de elementos da arvore rubro-negra
    }

    if (rbAtual == NULL) {  //se o no atual for nulo, define o novo no como raiz
        rb->sentinela->dir = novoNo;    //define o filho a direta do sentinela como o novo no
        novoNo->pai = rb->sentinela;    //define o pai do novo no como o sentinela
    }
    else {  //se o no atual nao for nulo, define o novo no como filho a direta do no atual
        if (rbAtual->chave > novoNo->chave) {   //se a chave do no atual for maior que a chave do novo no, define o novo no como filho a esquerda do no atual
            rbAtual->esq = novoNo;
        }
        else {  //se a chave do no atual for menor que a chave do novo no, define o novo no como filho a direta do no atual
            rbAtual->dir = novoNo;
        }
        novoNo->pai = rbAtual;  //define o pai do novo no como o no atual
    }

    if (btAtual->folha == 0) {  //se o no atual nao for folha, chama a funcao recursivamente para os filhos
        if (btAtual->ocupacao == 1) {   //se o no atual possuir apenas um filho, chama a funcao recursivamente para o filho
            converteNos(btAtual->ponteiros[0], novoNo, rb);
            converteNos(btAtual->ponteiros[1], novoNo, rb);
        }
        if (btAtual->ocupacao == 2) {   //se o no atual possuir dois filhos, chama a funcao recursivamente para os filhos
            converteNos(btAtual->ponteiros[0], novoNo, rb);
            converteNos(btAtual->ponteiros[1], novoNo->dir, rb);
            converteNos(btAtual->ponteiros[2], novoNo->dir, rb);
        }
        if (btAtual->ocupacao == 3) {   //se o no atual possuir tres filhos, chama a funcao recursivamente para os filhos
            converteNos(btAtual->ponteiros[0], novoNo->esq, rb);
            converteNos(btAtual->ponteiros[1], novoNo->esq, rb);
            converteNos(btAtual->ponteiros[2], novoNo->dir, rb);
            converteNos(btAtual->ponteiros[3], novoNo->dir, rb);
        }
    }

}

