#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "hash.h"

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

int main(void) {

  hash* h = criaHash(10);

  insere(h, "vanessa");

  // percorre(h, 0);

  printf("%d\n", getTamanhoLista(h, 3));

  // printf("%d\n", encontraElemento(h, "teste"));

  // printf("%d\n", encontraElemento(h, "teste2"));

  // printf("%d\n", encontraElemento(h, "teste7"));


  return 0;

}
