//
// Created by Vanessa on 22/04/2022.
//

#ifndef LISTA_4_MERGEQUICK_H
#define LISTA_4_MERGEQUICK_H


int geraAleatorios(char* nomeArquivo, int qtd);
//Esta função gera 'qtd' números aleatórios e os escreve no arquivo 'nomeArquivo'
//Os numeros devem variar entre 0 e 1000.
//A função retorna 0 se funcionou corretamente. Retorna 1 se houve algum erro no processo.
//Pesquisem pelas funções rand() e srand().

int* leArquivo(char* nomeArquivo, int qtd);
//Esta função lê 'qtd' dados do arquivo 'nomeArquivo' e os insere em um vetor de inteiros
//A função retorna NULL caso haja algum erro no processo.

void imprimeVet(int* vet, int tam);
//Esta função recebe um vetor e o imprime na tela
//A impressão é em linha -> printf("%d ", ...);
//Antes de encerrar, a função imprime uma linha em branco

void mergeSort(int* vet, int inicio, int fim);
//Função Mergesort Recursiva

void merge(int* vet, int inicio, int meio, int fim);
//Função Merge, que combina dois vetores previamente ordenados

void quickSort(int* vet, int inicio, int fim);
//Função QuickSort recursiva

int particiona(int* vet, int inicio, int fim);
//Função que ordena o elemento pivô.

#endif //LISTA_4_MERGEQUICK_H
