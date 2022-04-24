#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#define true 1
#define false 0

/*
    Luis Ricardo Albano Santos - 2021031844
    gcc -pedantic-errors -Wall main.c -o main.exe && ./main.exe
*/

// Função é a responsavel criar cada sequencia de dados, para cada tipo de dados 
// (aleatorio, crescente, decrescente), com o tamanho TAMS[i] passado (qtd), e o
// casos_teste (qtd de vezes que a sequencia de dados sera gerada)
bool gerarDados(char tipo, int qtd, int casos_teste) {

    FILE* abrirArquivoDados(char, int, bool, int);
    bool gerarDadosAleatorios(FILE*, int);
    bool gerarDadosCrescente(FILE*, int);
    bool gerarDadosDecrescente(FILE*, int);
    bool retorno = false;

    for (int i = 0; i < casos_teste; i++) {
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


// Função é a responsavel por abrir ou criar o arquivo de dados, para o tipo de dados,
// a quantidade de dados (qtd), se será para leitura ou escrita, e o caso_teste (numero do arquivo)
FILE* abrirArquivoDados(char tipo, int qtd, bool read, int caso_teste) {
    FILE* arquivo;
    char path[80] = "";
    char nome[20] = "";

    sprintf(nome, "%c_%d_%d.txt", tipo, caso_teste, qtd);

    switch (tipo) {
    case 'a':
        strcpy(path, "./casos_teste/aleatorios/");
        break;
    case 'c':
        strcpy(path, "./casos_teste/crescente/");
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
        if (!read) {
            printf("Erro ao abrir o arquivo %s\n", path);
            return NULL;
        }
        else {
            printf("Erro ao ler o arquivo %s\n", path);
            return NULL;
        }
    }

    return arquivo;
}

// Função é a responsavel por gerar os dados aleatorios, para o arquivo passado (arquivo),
// com a quantidade de dados (qtd) e salvar no arquivo
bool gerarDadosAleatorios(FILE* arquivo, int qtd) {
    srand(time(NULL));
    for (int i = 0; i < qtd; i++) {
        if (fprintf(arquivo, "%d\n", rand() % qtd) < 0) {
            return false;
        }
    }

    return true;
}

// Função é a responsavel por gerar os dados crescentes, para o arquivo passado (arquivo),
// com a quantidade de dados (qtd) e salvar no arquivo
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

// Função é a responsavel por gerar os dados decrescentes, para o arquivo passado (arquivo),
// com a quantidade de dados (qtd) e salvar no arquivo
bool gerarDadosDecrescente(FILE* arquivo, int qtd) {
    srand(time(NULL));
    long int dado = (qtd * (rand() % 10 + 1));

    for (int i = 0; i < qtd; i++) {
        if (fprintf(arquivo, "%ld\n", dado) < 0) {
            return false;
        }
        dado = dado - rand() % 10;
    }

    return true;
}

// Função é a responsavel por ler os dados do arquivo passado (arquivo), e retornar
int* lerDados(char tipo, int qtd, int caso_teste) {
    FILE* arquivo = abrirArquivoDados(tipo, qtd, true, caso_teste);
    int* dados = (int*)malloc(sizeof(int) * qtd);
    int i = 0;

    if (arquivo == NULL)
        return NULL;

    while (fscanf(arquivo, "%d", &dados[i]) != EOF) {
        i++;
    }

    fclose(arquivo);

    if (i != qtd) {
        printf("Erro ao ler arquivo.\n");
        free(dados);
        return NULL;
    }

    return dados;
}