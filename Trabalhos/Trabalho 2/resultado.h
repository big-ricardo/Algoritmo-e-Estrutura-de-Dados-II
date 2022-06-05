#ifndef RESULTADO_H
#define RESULTADO_H

typedef int bool;


// Struct que armazena as metricas dos resultados das ordenações
typedef struct {
    char tipo;
    int qtd;
    int caso;
    char* metodo;
    double tempo_carregar;
    double tempo_esvaziar;
    double tempo_consultar;
    unsigned long int rot_carregar;
    unsigned long int rot_esvaziar;
    int altura;
} Registro;

// Função responsável chamar o algoritmo de ordenação que le é passado
bool realizarOrdenacao(char, char, int, int);

// Função responsável por gerar o arquivo ou limpar caso já exista
bool zerarArquivosResultados();

#endif