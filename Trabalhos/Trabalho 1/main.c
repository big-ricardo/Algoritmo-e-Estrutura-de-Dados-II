#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#include "ordenacao.h"
#define true 1
#define false 0

// Numero de casos de teste que serão feitos para cada tamanho de vetor
#define CASOS_TESTE 10

typedef int bool;

// Chaves de identificação dos metodos de ordenação (ordenacao.c) implementados
const char N_METODOS[] = { 'm', 's', 'q' };

// Tamanho dos vetores de dados
const int TAMS[] = { 10000, 100000, 500000, 1000000 };

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

// Função é a responsavel por renderizar o menu de opções
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

  void renderizarProgresso(int, int, bool);

  int tam = sizeof(TAMS) / sizeof(TAMS[0]);
  int arquivos_gerados = 0;

  for (int i = 0; i < tam; i++, arquivos_gerados++) {

    renderizarProgresso(arquivos_gerados, tam, true);

    if (!gerarDados('a', TAMS[i], casos_teste))
      return false;
    if (!gerarDados('c', TAMS[i], casos_teste))
      return false;
    if (!gerarDados('d', TAMS[i], casos_teste))
      return false;
  }

  renderizarProgresso(arquivos_gerados, tam, true);

  return true;
}

// Função é a responsavel por chamar a função de ordenação com os casos de teste
// de TAM[i] para cada metodo de ordenação e tipo de dados (aleatorio, crescente, decrescente)
bool gerarResultados(int casos_teste) {

  void renderizarProgresso(int, int, bool);

  zerarArquivosResultados();

  int n_casos = sizeof(TAMS) / sizeof(TAMS[0]);
  int n_metodos = sizeof(N_METODOS) / sizeof(N_METODOS[0]);
  int testes_concluidos = 0, total = n_casos * n_metodos * n_metodos;

  for (int i = 0; i < n_casos; i++) {
    for (int j = 0; j < n_metodos; j++, testes_concluidos++) {
      renderizarProgresso(testes_concluidos, total, false);
      if (!realizarOrdenacao('a', N_METODOS[j], TAMS[i], casos_teste))
        return false;
    }
  }

  for (int i = 0; i < n_casos; i++) {
    for (int j = 0; j < n_metodos; j++, testes_concluidos++) {
      renderizarProgresso(testes_concluidos, total, false);
      if (!realizarOrdenacao('c', N_METODOS[j], TAMS[i], casos_teste))
        return false;
    }
  }

  for (int i = 0; i < n_casos; i++) {
    for (int j = 0; j < n_metodos; j++, testes_concluidos++) {
      renderizarProgresso(testes_concluidos, total, false);
      if (!realizarOrdenacao('d', N_METODOS[j], TAMS[i], casos_teste))
        return false;
    }
  }

  renderizarProgresso(testes_concluidos, total, false);

  return true;
}

// Função é a responsavel por renderizar o progresso do processo de gerar os dados de ordenação
void renderizarProgresso(int atual, int total, bool tipo) {
  system("clear || cls");
  printf("Progresso de %s:\n", tipo ? "Geracao de dados" : "Ordenacao");

  int porcentagem = (atual * 100) / total;

  for (int i = 0; i < porcentagem / 5; i++) {
    printf("#");
  }

  for (int i = porcentagem / 5; i < 20; i++) {
    printf(" ");
  }

  printf(" | %d %%\n", porcentagem);

}