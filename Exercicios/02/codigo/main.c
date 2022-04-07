#include <stdio.h>
#include <stdlib.h>
#include "bolha.h"
#define true 1
#define false 0
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

int main(void) {

  char nomeArquivo[30];

  tReturn* rep;

  rep = alocatReturn();

  // printf("Digite o nome do arquivo: ");
  scanf("%s", nomeArquivo);

  rep = leArquivo(nomeArquivo);

  if (getErro(rep) == 0) {
    bolha(getVet(rep), getTam(rep));
    imprimeVet(getVet(rep), getTam(rep));
  }
  else {
    trataErro(getErro(rep));
  }

  return 0;

}
