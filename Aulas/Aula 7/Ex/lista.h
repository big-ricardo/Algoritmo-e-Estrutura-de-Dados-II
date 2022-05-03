//
// Created by Vanessa on 30/04/2022.
//

#ifndef LISTA_5_LISTA_H
#define LISTA_5_LISTA_H

typedef struct lista lista;
typedef struct no no;

lista *criaLista();
//Aloca e inicializa uma lista

int insereLista(lista *l, char *palavra);
//Insere uma nova palavra na lista. Ou seja, aloca um nó, inicializa e o insere na lista.
//A insersão é sempre no começo da lista.
//Retorna 1 caso ocorra erro na inserção e 0 caso contrário.

lista *getLista(lista **vet, int pos);
//Retorna a lista de uma determinada posição da tabela hash

int getTamLista(lista *l);
//Retorna o tamanho de uma determinada lista

int buscaLista(lista *l, char *palavra);
//Verifica se uma palavra está presente ou não em uma lista
//Se a palavra estiver presente, retorna 1. Caso contrário, retorna 0;

void removeLista(lista *l, char *palavra);
//Remove uma palavra da lista

void imprimeLista(lista *l);
//Imprime as palavras de uma lista => printf("%s\n", noAux->palavra);
//Se a lista estiver vazia => printf("Lista Vazia\n");


#endif //LISTA_5_LISTA_H
