//
// Created by Vanessa on 30/04/2022.
//

#ifndef LISTA_5_HASH_H
#define LISTA_5_HASH_H

typedef struct hash hash;

hash *criaHash(int tam);
//Aloca e inicializa uma tabela hash de tamanho "tam";

int funcaoHash(char *palavra, int tamHash);
//Retorna a posição da palavra na tabela hash de tamanho "tamHash"
//O cálculo está na descrição da atividade

void insere(hash *h, char *palavra);
//Insere uma nova palavra na hash utilizando a função insereLista da TAD lista.

int encontraElemento(hash *h, char *palavra);
//Verifica a presença de uma palavra na tabela hash utilizando a função buscaLista da TAD lista
//Se o elemento estiver presente, retorna a posição dele na Hash. Caso contrário, retorna -1.

void percorre(hash *h, int pos);
//Imprime a lista de uma posição da hash utilizando a função imprimeLista da TAD lista

int getTamanhoLista(hash *h, int pos);
//Retorna o tamanho de uma lista da hash utilizando a função getTamLista da TAD lista.

int removeElemento(hash *h, char *palavra);
//Remove uma palavra da hash utilizando as funções encontraElemento e removeLista da TAD lista.
//Se o elemento existia na hash e foi removido, retorna 0. Caso contrário, retorna -1.


#endif //LISTA_5_HASH_H
