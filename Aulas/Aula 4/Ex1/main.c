#include <stdio.h>
#include <stdlib.h>
#include "selecaoInsercao.h"
#define true 1
#define false 0
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

int main(void) {

  char arquivo[20] = "arquivo.txt";
  int qtd = 10;
  int* vetor = NULL;

  geraAleatorios(arquivo, qtd);
  vetor = leArquivo(arquivo, qtd);
  imprimeVet(vetor, qtd);

  selecao(vetor, qtd);
  // imprimeVet(vetor, qtd);

  vetor = leArquivo(arquivo, qtd);
  selecaoDecrescente(vetor, qtd);
  // imprimeVet(vetor, qtd);

  vetor = leArquivo(arquivo, qtd);
  dualSelecao(vetor, qtd);
  imprimeVet(vetor, qtd);

  vetor = leArquivo(arquivo, qtd);
  insercao(vetor, qtd);
  imprimeVet(vetor, qtd);

  return 0;

}
