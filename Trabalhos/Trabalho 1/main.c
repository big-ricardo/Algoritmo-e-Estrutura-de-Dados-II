#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#include "ordenacao.h"
#define true 1
#define false 0
#define CASOS_TESTE 1
typedef int bool;

/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

const char N_METODOS[] = { 's', 'q', 'm' };

const int TAMS[] = { 1000 };

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
    system("clear || cls");
    switch (opcao) {
    case '1':
      gerarCasos(CASOS_TESTE);
      gerarResultados(CASOS_TESTE);
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

bool gerarResultados(int casos_teste) {

  zerarArquivosResultados();

  int n_casos = sizeof(TAMS) / sizeof(TAMS[0]);
  int n_metodos = sizeof(N_METODOS) / sizeof(N_METODOS[0]);

  for (int i = 0; i < n_casos; i++) {
    for (int j = 0; j < n_metodos; j++) {
      if (!realizarOrdenacao('a', N_METODOS[j], TAMS[i], casos_teste))
        return false;
    }
  }

  for (int i = 0; i < n_casos; i++) {
    for (int j = 0; j < n_metodos; j++) {
      if (!realizarOrdenacao('c', N_METODOS[j], TAMS[i], casos_teste))
        return false;
    }
  }

  for (int i = 0; i < n_casos; i++) {
    for (int j = 0; j < n_metodos; j++) {
      if (!realizarOrdenacao('d', N_METODOS[j], TAMS[i], casos_teste))
        return false;
    }
  }

  printf("Ordenacao realizada com sucesso\n");

  return true;
}