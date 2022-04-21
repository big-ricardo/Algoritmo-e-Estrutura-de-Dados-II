#include <stdlib.h>

/*
    Este arquivo é responsavel por toda manipulação dos dados,
    gerar os conjuntos de dados e a leitura deles.
*/

#ifndef DADOS_H
#define DADOS_H

typedef int bool;

// Função é a responsavel por gerar os conjuntos de dados, para cada tamanho TAMS[i]
bool gerarDados(char, int, int);

// Função é a responsavel por criar o vetor, fazer a leitura do arquivo e
// retornar o vetor com os dados
int* lerDados(char, int, int);

#endif 