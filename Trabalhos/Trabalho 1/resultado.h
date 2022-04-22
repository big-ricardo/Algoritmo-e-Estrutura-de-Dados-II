#ifndef RESULTADO_H
#define RESULTADO_H

typedef int bool;

typedef struct {
    double tempo;
    unsigned long int comparacoes;
    unsigned long int copias;
    char tipo;
    int qtd;
    int caso;
    char* metodo;
} Registro;

bool realizarOrdenacao(char, char, int, int);

bool zerarArquivosResultados();

#endif