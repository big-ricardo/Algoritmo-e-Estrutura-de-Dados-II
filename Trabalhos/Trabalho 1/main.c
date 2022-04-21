#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define true 1
#define false 0
#define CASOS_TESTE 2
typedef int bool;

const int TAMS[4] = { 10000, 1000000, 500000, 1000000 };
// const int TAMS[2] = { 5, 10 };
/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

int main(void) {

  void renderizarMenu(bool);
  bool gerarCasosTeste();

  char buff[5], opcao;
  bool error = false;

  do {
    renderizarMenu(error);
    printf("Digite a opcao desejada: ");
    fgets(buff, 5, stdin);
    sscanf(buff, "%c", &opcao);
    switch (opcao) {
    case '1':
      gerarCasosTeste();
      break;
    case '2':
      gerarCasosTeste();
      break;
    case '3':
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
  system("clear || cls");
  printf("-----------------Menu----------------\n");
  printf("1. Gerar Dados e Resultado\n");
  printf("2. Gerar Dados\n");
  printf("3. Gerar Resultado\n");
  printf("4. Sair\n");
  printf("---------------------------------------\n");
  if (error)
    printf("Opção inválida!\n");
}

bool gerarCasosTeste() {
  bool gerarDados(char, int);

  int tam = sizeof(TAMS) / sizeof(TAMS[0]);

  for (int i = 0; i < tam; i++) {
    if (!gerarDados('a', TAMS[i]))
      return false;
    if (!gerarDados('c', TAMS[i]))
      return false;
    if (!gerarDados('d', TAMS[i]))
      return false;
  }

  return true;

}

bool gerarDados(char tipo, int qtd) {

  FILE* abrirArquivoDados(char, int, bool, int);
  bool gerarDadosAleatorios(FILE*, int);
  bool gerarDadosCrescente(FILE*, int);
  bool gerarDadosDecrescente(FILE*, int);
  bool retorno = false;

  for (int i = 0; i < CASOS_TESTE; i++) {
    FILE* arquivo = abrirArquivoDados(tipo, qtd, false, i);

    if (arquivo == NULL)
      return false;

    switch (tipo) {
    case 'a':
      retorno = gerarDadosAleatorios(arquivo, qtd);
      break;
    case 'c':
      retorno = gerarDadosCrescente(arquivo, qtd);
      break;
    case 'd':
      retorno = gerarDadosDecrescente(arquivo, qtd);
      break;
    }

    fclose(arquivo);

    if (!retorno)
      return false;
  }

  return retorno;
}

FILE* abrirArquivoDados(char tipo, int qtd, bool read, int indice) {
  FILE* arquivo;
  char path[50] = "";
  char nome[15] = "";

  sprintf(nome, "%d_%d.txt", indice, qtd);

  switch (tipo) {
  case 'a':
    strcpy(path, "./casos_teste/aleatorios/");
    break;
  case 'c':
    strcpy(path, "./casos_teste/cresecente/");
    break;
  case 'd':
    strcpy(path, "./casos_teste/decresente/");
    break;
  default:
    return NULL;
  }

  strcat(path, nome);
  arquivo = fopen(path, read ? "r" : "w+");

  if (arquivo == NULL) {
    printf("Erro ao criar arquivo.\n");
  }

  return arquivo;
}

bool gerarDadosAleatorios(FILE* arquivo, int qtd) {
  srand(time(NULL));
  for (int i = 0; i < qtd; i++) {
    if (fprintf(arquivo, "%d\n", rand() % qtd) < 0) {
      return false;
    }
  }

  return true;
}

bool gerarDadosCrescente(FILE* arquivo, int qtd) {
  srand(time(NULL));
  int dado = rand() % 100 + 1;

  for (int i = 0; i < qtd; i++) {
    if (fprintf(arquivo, "%d\n", dado) < 0) {
      return false;
    }
    dado = dado + rand() % 100;
  }

  return true;
}

bool gerarDadosDecrescente(FILE* arquivo, int qtd) {
  srand(time(NULL));
  long int dado = (qtd * 10) + (rand() % 100);

  for (int i = 0; i < qtd; i++) {
    if (fprintf(arquivo, "%ld\n", dado) < 0) {
      return false;
    }
    dado = dado - rand() % 10;
  }

  return true;
}