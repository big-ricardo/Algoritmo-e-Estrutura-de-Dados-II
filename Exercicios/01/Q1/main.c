#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define N 100
#define arqA "dadosA.txt"
#define arqB "dadosB.txt"

typedef int bool;


/*
  Luis Ricardo Albano Santos - 2021031844
  gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

void mostrarDados(int *dados, int tam){ 
  for(int i= 0; i<tam;){
    \
    for(int j=0; j<5; j++){
      printf("%d\t", dados[i++]);
    }
    printf("\n");
  }
}

bool lerDados(FILE* A, int *dadosA, FILE* B, int *dadosB) {
  A = fopen(arqA, "r");
  B = fopen(arqB, "r");
  if (A == NULL || B == NULL) return false;

  int aux;

  for(int i= 0; fscanf(A, "%d", &aux)!=EOF; i++){
    dadosA[i] = aux;
  }

  for(int i= 0; fscanf(B, "%d", &aux)!=EOF; i++){
    dadosB[i] = aux;
  }

  return true;
}

void ordena(int* V, int nV) {
  int aux;
  //Percorro o vetor 
  for (int i = 0; i < nV - 1; i++) {
    //Ordeno o vetor fazendo ele rodar cada vez menos, otimizando assim
    for (int j = 0; j < nV - i - 1; j++) {
      if (V[j] > V[j + 1]) {
        //realizo a troca
        aux = V[j];
        V[j] = V[j + 1];
        V[j + 1] = aux;
      }
    }
  }
}

bool fundirDados(int *dadosA, int* dadosB, int* dadosC) {
  
  for (int i = 0; i < N; i++) {
    dadosC[i] = dadosA[i];
  }

  for (int i = 0; i < N; i++) {
    dadosC[i + N] = dadosB[i];
  }

  ordena(dadosC, N*2);

  return true;
}

int main(void) {

  FILE* A = NULL;
  FILE* B = NULL;
  int dadosA[N], dadosB[N], dadosC[N*2];
  int menu;
  bool dadosLidos = false;

  do {
    printf("------------------Menu------------------\n");
    printf("1 - Carregar Dados\n");
    printf("2 - Unir os Dados\n");
    printf("3 - Mostrar os Dados\n");
    printf("4 - Sair\n");
    printf("----------------------------------------\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &menu);

    switch (menu) {
    case 1:
      if (lerDados(A, dadosA, B, dadosB)) {
        system("cls ||clear");
        printf("Dados carregados com sucesso.\n");
        dadosLidos = true;
      }
      else {
        system("cls ||clear");
        printf("Erro ao carregar os dados.\n");
        return 1;
      }
      break;
    case 2:
      if (dadosLidos) {
        fundirDados(dadosA, dadosB, dadosC);
        system("cls ||clear");
        printf("Dados unidos com sucesso.\n");
      }
      else {
        system("cls ||clear");
        printf("Erro ao unir os dados.\n");
      }
      break;
    case 3:
      if (dadosLidos) {
        system("cls ||clear");
        printf("Dados:\n");
        mostrarDados(dadosC, N*2);
        printf("\n");
        printf("Digite 0 para continuar...\n");
        scanf("%d", &menu);
        system("cls ||clear");
      }
      else {
        system("cls ||clear");
        printf("Erro ao mostrar os dados.\n");
      }
      break;
    case 4:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida\n");
      break;
    }

  } while (menu != 4);

  return 0;

}
