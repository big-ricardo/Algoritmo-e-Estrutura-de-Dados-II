#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#define true 1
#define false 0
#define CASOS_TESTE 2
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

const int TAMS[2] = { 10, 20 };

int main(void) {

  void renderizarMenu(bool);
  bool gerarCasos(int);
  bool gerarResultados(int);

  char buff[5], opcao;
  bool error = false;

  do {
    renderizarMenu(error);
    printf("Digite a opcao desejada: ");
    fgets(buff, 5, stdin);
    sscanf(buff, "%c", &opcao);
    switch (opcao) {
    case '1':
      gerarCasos(CASOS_TESTE);
      break;
    case '2':
      gerarCasos(CASOS_TESTE);
      break;
    case '3':
      gerarResultados(CASOS_TESTE);
      break;
    case '4':
      break;
    default:
      error = true;
    }

  } while (opcao != '4');

  return 0;
}

void renderizarMenu(bool error) {
  // system("clear || cls");
  printf("-----------------Menu----------------\n");
  printf("1. Gerar Dados e Resultado\n");
  printf("2. Gerar Dados\n");
  printf("3. Gerar Resultado\n");
  printf("4. Sair\n");
  printf("---------------------------------------\n");
  if (error)
    printf("Opção inválida!\n");
}

// Função é a responsavel por chamar a função para gerar os conjuntos de dados, 
// para cada tamanho TAMS[i]
bool gerarCasos(int casos_teste) {

  int tam = sizeof(TAMS) / sizeof(TAMS[0]);

  for (int i = 0; i < tam; i++) {
    if (!gerarDados('a', TAMS[i], casos_teste))
      return false;
    if (!gerarDados('c', TAMS[i], casos_teste))
      return false;
    if (!gerarDados('d', TAMS[i], casos_teste))
      return false;
  }

  return true;
}

bool realizarOrdenacao(char tipo, bool funcao(int*, int), int tam, int casos_teste) {

  for (int j = 0; j < casos_teste; j++) {
    int* dados = lerDados(tipo, tam, j);

    if (dados == NULL) {
      free(dados);
      return false;
    }

    free(dados);
  }

  return true;
}

bool gerarResultados(int casos_teste) {

  int tam = sizeof(TAMS) / sizeof(TAMS[0]);

  for (int i = 0; i < tam; i++) {

    if (!realizarOrdenacao('a', NULL, TAMS[i], casos_teste))
      return false;

    if (!realizarOrdenacao('c', NULL, TAMS[i], casos_teste))
      return false;

    if (!realizarOrdenacao('d', NULL, TAMS[i], casos_teste))
      return false;

  }

  return true;
}