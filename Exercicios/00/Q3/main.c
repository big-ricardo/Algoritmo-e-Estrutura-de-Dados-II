#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

int buscaLinear(FILE* V, int index, int chave) {
  int aux = 0;
  if (fscanf(V, "%d", &aux) == EOF)
    return -1;

  if (aux == chave)
    return index;

  return buscaLinear(V, index + 1, chave);
}

int main(void) {

  FILE* V;
  int chave = 0;

  V = fopen("dadosA.txt", "r");

  if (V == NULL) {
    printf("Erro na abertura do arquivo\n");
    return 1;
  }

  scanf("%d", &chave);

  int index = buscaLinear(V, 0, chave);

  printf("%d\n", index);

  return 0;
}
