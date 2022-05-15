#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "hash.h"

/*
  Diovana Tavares dos Reis - 2021016991
  Luis Ricardo Albano Santos - 2021031844
*/

struct hash {
    lista** tabela;
    int tamanho;
};


//Aloca e inicializa uma tabela hash de tamanho "tam";
hash* criaHash(int tam) {
    hash* h = (hash*)malloc(sizeof(hash));
    if (h == NULL) {
        printf("Erro ao alocar memória para a tabela hash.\n");
        return NULL;
    }

    h->tabela = (lista**)malloc(tam * sizeof(lista*));
    if (h->tabela == NULL) {
        printf("Erro ao alocar memória para a tabela hash.\n");
        return NULL;
    }
    h->tamanho = tam;

    for (int i = 0; i < tam; i++) {
        h->tabela[i] = criaLista();
    }

    return h;
}

//Retorna a posição da palavra na tabela hash de tamanho "tamHash"
//O cálculo está na descrição da atividade
int funcaoHash(char* palavra, int tamHash) {
    int soma = 0;
    int tam = strlen(palavra);
    for (int i = 0;i < tam; i++) {
        soma += palavra[i];
    }

    return soma % tamHash;
}

//Insere uma nova palavra na hash utilizando a função insereLista da TAD lista.
void insere(hash* h, char* palavra) {
    int pos = funcaoHash(palavra, h->tamanho);
    insereLista(h->tabela[pos], palavra);
}

//Verifica a presença de uma palavra na tabela hash utilizando a função buscaLista da TAD lista
//Se o elemento estiver presente, retorna a posição dele na Hash. Caso contrário, retorna -1.
int encontraElemento(hash* h, char* palavra) {
    int pos = funcaoHash(palavra, h->tamanho);

    if (buscaLista(h->tabela[pos], palavra)) {
        return pos;
    }

    return -1;
}

//Imprime a lista de uma posição da hash utilizando a função imprimeLista da TAD lista
void percorre(hash* h, int pos) {
    imprimeLista(h->tabela[pos]);
}

//Retorna o tamanho de uma lista da hash utilizando a função getTamLista da TAD lista.
int getTamanhoLista(hash* h, int pos) {
    return getTamLista(h->tabela[pos]);
}

//Remove uma palavra da hash utilizando as funções encontraElemento e removeLista da TAD lista.
//Se o elemento existia na hash e foi removido, retorna 0. Caso contrário, retorna -1.
int removeElemento(hash* h, char* palavra) {
    int pos = funcaoHash(palavra, h->tamanho);
    if (encontraElemento(h, palavra) != -1) {
        removeLista(h->tabela[pos], palavra);
        return 0;
    }
    return -1;
}