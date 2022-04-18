//
// Created by Vanessa on 18/04/2022.
//

#ifndef LISTA_3_SELECAOINSERCAO_H
#define LISTA_3_SELECAOINSERCAO_H

int geraAleatorios(char *nomeArquivo, int qtd);
//Esta função gera 'qtd' números aleatórios e os escreve no arquivo 'nomeArquivo'
//Os numeros devem variar entre 0 e 1000.
//A função retorna 0 se funcionou corretamente. Retorna 1 se houve algum erro no processo.
//Pesquisem pelas funções rand() e srand().

int* leArquivo(char *nomeArquivo, int qtd);
//Esta função lê 'qtd' dados do arquivo 'nomeArquivo' e os insere em um vetor de inteiros
//A função retorna NULL caso haja algum erro no processo.

void selecao(int *vet, int tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem crescente) utilizando o método seleção

void selecaoDecrescente(int *vet, int tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem decrescente) utilizando o método seleção

void dualSelecao(int *vet, int tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena utilizando o método dual seleção

void insercao(int *vet, int tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena utilizando o método insercao

void imprimeVet(int *vet, int tam);
//Esta função recebe um vetor e o imprime na tela
//A impressão é em linha -> printf("%d ", vet[i]);
//Antes de encerrar, a função imprime uma linha em branco


#endif //LISTA_3_SELECAOINSERCAO_H
