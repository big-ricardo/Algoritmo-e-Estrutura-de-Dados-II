#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

int somaV(FILE* V, int soma) {
  int aux = 0;
  if (fscanf(V, "%d", &aux) == EOF)
    return 0;

  soma += aux + somaV(V, soma);

  return soma;
}

int main(void) {

  FILE* V;

  V = fopen("dadosA.txt", "r");

  if (V == NULL) {
    printf("Erro na abertura do arquivo\n");
    return 1;
  }

  int soma = somaV(V, 0);

  printf("Soma dos dados: %d\n", soma);

  return 0;
}
