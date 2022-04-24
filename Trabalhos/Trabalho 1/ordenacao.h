#include "resultado.h"

#ifndef ORDENACAO_H
#define ORDENACAO_H

// Algoritmo de ordenação selectionSort
void selecao(Registro*, int*, int);

// Algoritmo de ordenação quickSort
void quickSort(Registro*, int*, int, int);

// Algoritmo de ordenação apresentado pelo artigo 
void mobileSort(Registro*, int*, int);

// Função responsável por gerar o arquivo ou limpar caso já exista com os 
//resultados das ordenações
bool criarArquivoOrdenacao(char*);

// Função responsável por salvar os resultados das ordenações no arquivo de texto
bool salvarOrdenacao(Registro, int*, int);

#endif