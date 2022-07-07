#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

/*
  Luis Ricardo Albano Santos - 2021031844
  Matheus Martins Batista 2019005687
*/

struct no {
    int* chaves;
    no** ponteiros;
    no* pai;
    int folha;
    int ocupacao;
};

struct btree {
    int ordem;
    no* raiz;
};

//Função que aloca e inicializa um novo nó
no* alocaNo(int ordem) {
    no* novoNo = (no*)malloc(sizeof(no));
    if (novoNo == NULL) {
        printf("Erro ao alocar novo nó\n");
        return NULL;
    }
    novoNo->chaves = (int*)malloc(sizeof(int) * (ordem - 1));
    if (novoNo->chaves == NULL) {
        printf("Erro ao alocar chaves\n");
        return NULL;
    }
    novoNo->ponteiros = (no**)malloc(sizeof(no*) * (ordem));
    if (novoNo->ponteiros == NULL) {
        printf("Erro ao alocar ponteiros\n");
        return NULL;
    }

    for (int i = 0; i < ordem; i++) {
        novoNo->ponteiros[i] = NULL;
    }

    novoNo->pai = NULL;
    novoNo->folha = 1;
    novoNo->ocupacao = 0;
    return novoNo;
}


//Função que aloca e inicializa uma nova árvore com uma raiz alocada, porém vazia.
//Árvore B tradicional. A ordem m deve ser sempre par. Caso contrário, retorna NULL.
btree* criaArvore(int m) {
    if (m % 2 == 0) {
        btree* arvore = (btree*)malloc(sizeof(btree));
        if (arvore == NULL) {
            printf("Erro ao alocar arvore\n");
            return NULL;
        }
        arvore->ordem = m;
        arvore->raiz = alocaNo(m);
        if (arvore->raiz == NULL) {
            printf("Erro ao alocar raiz\n");
            return NULL;
        }
        return arvore;
    }
    else {
        printf("Erro ao criar arvore\n");
        return NULL;
    }
}

//Função que retorna a raiz da árvore
no* retornaRaiz(btree* arvore) {
    return arvore->raiz;
}

//Função recursiva que imprime a árvore por profundidade
//Raiz, filho da esquerda até chegar na folha. E sobe imprimindo os filhos em sequência
void imprimeArvore(no* atual, int filho) {
    if (atual == NULL) return;

    if (atual->ocupacao == 0) {
        printf("Vazio");

        return;
    }

    if (atual->folha == 1) {
        for (int i = 0; i < atual->ocupacao; i++) {
            printf("%d ", atual->chaves[i]);
        }
        printf(" : F\n");
    }
    else {
        for (int i = 0; i < atual->ocupacao; i++) {
            printf("%d ", atual->chaves[i]);
        }
        printf(" : N Folha\n");
        for (int i = 0; i <= atual->ocupacao; i++) {
            imprimeArvore(atual->ponteiros[i], i);
        }
    }
}

//Função recursiva que retorna o nó onde o elemento está na árvore
no* buscaElemento(no* atual, int valor) {
    if (atual == NULL) return NULL;
    int i = 0;
    while (i < atual->ocupacao && valor > atual->chaves[i]) i++;
    if (i < atual->ocupacao && valor == atual->chaves[i]) return atual;
    if (atual->folha == 1) return NULL;
    return buscaElemento(atual->ponteiros[i], valor);
}

//Função que insere um novo elemento na árvore.
//Encontra a folha correta, realiza a inserção em árvore B tradicional
//Ou seja, se a folha estiver cheia, primeiro realiza o split e depois insere
//Se houve a inserção, retorna 1. Caso contrário, retorna -1
int insereElemento(btree* arvore, int valor) {
    no* atual = arvore->raiz;
    int c = atual->ocupacao;

    if (atual->ponteiros[0] == NULL && c < arvore->ordem - 1) {
        while (c < arvore->ordem - 1) {
            if (valor < atual->chaves[c]) {
                atual->chaves[c] = valor;
                atual->ocupacao++;
                return 1;
            }
            c++;
        }
    }
    else {
        while (atual->folha == 0) {
            int i = 0;
            while (i < atual->ocupacao && valor >= atual->chaves[i]) i++;
            atual = atual->ponteiros[i];
        }
    }

    if (atual->ocupacao == arvore->ordem - 1) {
        atual = split(arvore, atual, valor);
    }

    c = atual->ocupacao;
    while (c > 0 && atual->chaves[c - 1] > valor) {
        atual->chaves[c] = atual->chaves[c - 1];
        c--;
    }

    atual->chaves[c] = valor;
    atual->ocupacao++;

    return 1;
}

//Função que remove um elemento da B-Tree
//Na remoção por cópia, usar o predecessor
//No caso de rotação e merge, tentar primeiro o irmão da esquerda e depois o da direita
//Se houve a remoção, retorna 1. Caso contrário, retorna -1
int removeElemento(btree* arvore, int valor) {

    no* noRemove = buscaElemento(arvore->raiz, valor);
    no* noAux;

    if (noRemove == NULL) {
        printf("Elemento não encontrado\n");
        return -1;
    }

    if (noRemove->folha == 0) {
        int i = 0;
        while (i < noRemove->ocupacao && valor > noRemove->chaves[i]) i++;
        noAux = noRemove->ponteiros[i];
        while (noAux->ponteiros[noAux->ocupacao - 1] != NULL) {
            noAux = noAux->ponteiros[noAux->ocupacao];
        }
        noRemove->chaves[i] = noAux->chaves[noAux->ocupacao - 1];
        noRemove = noAux;
        valor = noRemove->chaves[noRemove->ocupacao - 1];
    }

    int i = 0;
    while (i < noRemove->ocupacao && valor > noRemove->chaves[i]) i++;

    while (i < noRemove->ocupacao) {
        noRemove->chaves[i] = noRemove->chaves[i + 1];
        i++;
    }
    noRemove->ocupacao--;

    while (noRemove != NULL && noRemove->ocupacao < (arvore->ordem - 1) / 2 && noRemove != arvore->raiz) {
        no* pai = noRemove->pai;
        int indice = 0;
        while (indice < pai->ocupacao && valor > pai->chaves[indice]) indice++;

        if (indice > 0 && pai->ponteiros[indice - 1]->ocupacao > (arvore->ordem - 1) / 2) {
            rotacao(noRemove, pai->ponteiros[indice - 1], indice);
        }
        else if (indice < pai->ocupacao && pai->ponteiros[indice + 1]->ocupacao >(arvore->ordem - 1) / 2) {
            rotacao(noRemove, pai->ponteiros[indice + 1], indice);
        }
        else {
            noRemove = merge(noRemove, indice);
            if (noRemove->pai == arvore->raiz && noRemove->pai->ocupacao == 0) {
                free(noRemove->pai);
                arvore->raiz = noRemove;
                noRemove->pai = NULL;
            }
            noRemove = noRemove->pai;
        }
    }

    return 1;

}

//Função que realiza o split no noDesbal. A variável valor guarda o elemento que está sendo inserido (e que causou o split)
//Função chamada pela função insereElemento
//Sempre sobe o elemento do meio para o pai (m é sempre par).
//Caso o pai esteja cheio, a função se chama recursivamente.
no* split(btree* arvore, no* noDesbal, int valor) {


    int meio = (arvore->ordem - 1) / 2;
    no* pai = noDesbal->pai;
    no* novoNo = alocaNo(arvore->ordem);
    int chaveMeio = noDesbal->chaves[meio];

    novoNo->folha = noDesbal->folha;
    novoNo->pai = noDesbal->pai;
    int i = 0, aux = meio + 1;

    for (; aux < arvore->ordem - 1; i++, aux++) {
        novoNo->chaves[i] = noDesbal->chaves[aux];
        novoNo->ocupacao++;
        noDesbal->ocupacao--;

        if (novoNo->folha == 0) {
            novoNo->ponteiros[i] = noDesbal->ponteiros[aux];
            noDesbal->ponteiros[aux]->pai = novoNo;
        }
        noDesbal->ponteiros[aux] = NULL;
    }

    if (novoNo->folha == 0) {
        novoNo->ponteiros[i] = noDesbal->ponteiros[aux];
        noDesbal->ponteiros[aux]->pai = novoNo;
    }

    novoNo->ponteiros[aux] = NULL;

    if (pai == NULL) {
        no* novaRaix = alocaNo(arvore->ordem);
        novaRaix->folha = 0;
        novaRaix->pai = NULL;
        novaRaix->chaves[0] = chaveMeio;
        novaRaix->ocupacao++;
        noDesbal->ocupacao--;
        novaRaix->ponteiros[0] = noDesbal;
        novaRaix->ponteiros[1] = novoNo;
        noDesbal->pai = novaRaix;
        novoNo->pai = novaRaix;
        arvore->raiz = novaRaix;

        if (valor < chaveMeio) {
            return noDesbal;
        }
        else {
            return novoNo;
        }
    }
    else {
        i = pai->ocupacao;

        if (i == arvore->ordem - 1) {
            pai = split(arvore, pai, chaveMeio);
            i = pai->ocupacao;
        }

        while (i > 0 && pai->chaves[i - 1] > chaveMeio) {
            pai->chaves[i] = pai->chaves[i - 1];
            pai->ponteiros[i + 1] = pai->ponteiros[i];
            i--;
        }
        pai->chaves[i] = chaveMeio;
        pai->ponteiros[i + 1] = novoNo;
        pai->ocupacao++;
        noDesbal->ocupacao--;
        novoNo->pai = pai;
    }

    if (valor < chaveMeio) {
        return noDesbal;
    }
    else {
        return novoNo;
    }

}

//Função que implementa a rotação, levanto um elemento do pai para o nóDesbal e subindo um elemento do no irmão para o pai
// A variável posPai guarda a posição do ponteiro do pai que aponta para o nó noDesbal
void rotacao(no* noDesbal, no* irmao, int posPai) {
    no* pai = irmao->pai;

    if (pai->ponteiros[posPai - 1] == irmao) {

        for (int i = noDesbal->ocupacao; i > 0; i--) {
            noDesbal->chaves[i] = noDesbal->chaves[i - 1];
            noDesbal->ponteiros[i + 1] = noDesbal->ponteiros[i];
        }
        noDesbal->chaves[0] = pai->chaves[posPai - 1];
        if (noDesbal->folha == 0) {
            noDesbal->ponteiros[posPai - 1] = irmao->ponteiros[posPai];
            irmao->ponteiros[posPai - 1]->pai = noDesbal;
        }
        noDesbal->ocupacao++;

        pai->chaves[posPai - 1] = irmao->chaves[irmao->ocupacao - 1];
        irmao->ocupacao--;
    }
    else {
        noDesbal->chaves[noDesbal->ocupacao] = pai->chaves[posPai];
        noDesbal->ocupacao++;

        pai->chaves[posPai] = irmao->chaves[0];
        irmao->ocupacao--;

        for (int i = 0; i < irmao->ocupacao; i++) {
            irmao->chaves[i] = irmao->chaves[i + 1];
            irmao->ponteiros[i] = irmao->ponteiros[i + 1];
        }
    }
}

//Função que implementa o merge do nó Desbal com seu irmão da esquerda ou da direita
//Se a variãvel posPai é maior que zero, o merge acontece com o irmão da esquerda
//Caso contrário, com o irmão da direita
no* merge(no* noDesbal, int posPai) {
    no* pai = noDesbal->pai;

    if (posPai > 0) {

        no* irmao = pai->ponteiros[posPai - 1];
        irmao->chaves[irmao->ocupacao] = pai->chaves[posPai - 1];
        irmao->ocupacao++;
        for (int i = 0; i < noDesbal->ocupacao; i++) {
            irmao->chaves[irmao->ocupacao] = noDesbal->chaves[i];
            irmao->ponteiros[irmao->ocupacao] = noDesbal->ponteiros[i];
            irmao->ocupacao++;
        }
        irmao->ponteiros[irmao->ocupacao] = noDesbal->ponteiros[noDesbal->ocupacao];
        if (irmao->folha == 0) {
            for (int i = 0; i <= irmao->ocupacao; i++) {
                irmao->ponteiros[i]->pai = irmao;
            }
        }
        for (int i = posPai; i <= pai->ocupacao; i++) {
            pai->chaves[i - 1] = pai->chaves[i];
            pai->ponteiros[i] = pai->ponteiros[i + 1];
        }
        pai->ocupacao--;

        irmao->pai = pai;

        free(noDesbal);

        return irmao;
    }
    else {
        no* irmao = pai->ponteiros[posPai + 1];
        noDesbal->chaves[noDesbal->ocupacao] = pai->chaves[posPai];
        noDesbal->ocupacao++;
        for (int i = 0; i < irmao->ocupacao; i++) {
            noDesbal->chaves[noDesbal->ocupacao] = irmao->chaves[i];
            noDesbal->ponteiros[noDesbal->ocupacao] = irmao->ponteiros[i];
            noDesbal->ocupacao++;
        }
        noDesbal->ponteiros[noDesbal->ocupacao] = irmao->ponteiros[irmao->ocupacao];
        if (noDesbal->folha == 0) {
            for (int i = 0; i <= noDesbal->ocupacao; i++) {
                noDesbal->ponteiros[i]->pai = noDesbal;
            }
        }
        for (int i = posPai + 1; i <= pai->ocupacao; i++) {
            pai->chaves[i - 1] = pai->chaves[i];
            pai->ponteiros[i] = pai->ponteiros[i + 1];
        }
        pai->ocupacao--;

        free(irmao);

        return noDesbal;
    }

}


//Função que lê dados do arquivo nomeArquivo e os insere ou remove da B-Tree arvore
//Se o status for "i", a função deve inserir todos os elementos do arquivo na árvore
//Se o status for "r", a função deve remover todos os elementos do arquivo da árvore
void manipulaBTree(btree* arvore, char* nomeArquivo, char status) {
    FILE* arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    int chave;
    while (fscanf(arq, "%d", &chave) != EOF) {
        if (status == 'i') {
            insereElemento(arvore, chave);
            printf("\n ###Inserir %d\n", chave);
            imprimeArvore(arvore->raiz, 0);
        }
        else if (status == 'r') {
            removeElemento(arvore, chave);
            printf("\n ###Remover %d\n", chave);
            imprimeArvore(arvore->raiz, 0);
        }
    }
    fclose(arq);
}