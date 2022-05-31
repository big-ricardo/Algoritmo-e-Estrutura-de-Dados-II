#ifndef RESULTADO_H
#define RESULTADO_H

typedef int bool;


// Struct que armazena as metricas dos resultados das ordenações
typedef struct {
    double tempo;
    unsigned long int comparacoes;
    unsigned long int copias;
    char tipo;
    int qtd;
    int caso;
    char* metodo;
} Registro;

// Função responsável chamar o algoritmo de ordenação que le é passado
bool realizarOrdenacao(char, char, int, int);

// Função responsável por gerar o arquivo ou limpar caso já exista
bool zerarArquivosResultados();

#endif