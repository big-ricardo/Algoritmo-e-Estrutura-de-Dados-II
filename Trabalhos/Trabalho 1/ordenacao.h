#include "resultado.h"

#ifndef ORDENACAO_H
#define ORDENACAO_H

void selecao(Registro*, int*, int);

void quickSort(Registro*, int*, int, int);

void mobileSort(Registro*, int*, int);

bool criarArquivoOrdenacao(char*);

bool salvarOrdenacao(Registro, int*, int);

#endif