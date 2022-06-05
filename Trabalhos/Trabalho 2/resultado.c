#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dados.h"
#include "resultado.h"
#include "avl.h"

#define true 1
#define false 0

#define RESULTADO_TXT "./resutados/r" // path base dos arquivos de resultados

#define AVL "AVL" // nome do algoritmo de ordenação
#define BINARIA "BINARY_TREE" // nome do algoritmo de ordenação

#define AUDITORIA false // Se true, gera os arquivos que salvam as ordenações feitas

bool computarDadosAVL(Registro* r, FILE* arq) {
    ArvAVL* avl = cria_ArvAVL();

    clock_t inicio, fim;
    inicio = clock();

    carregaArvoreAvl(r, avl, arq);

    fim = clock();
    r->tempo_carregar = (double)(fim - inicio) / CLOCKS_PER_SEC;

    r->altura = altura_No(((No*)avl));

    clock_t inicio2, fim2;

    inicio2 = clock();
    for (int i = 0; i < 30; i++) {
        busca_ArvAVL(avl, rand() % r->qtd);
    }
    fim2 = clock();
    r->tempo_consultar = (double)((fim2 - inicio2) / CLOCKS_PER_SEC);

    // int* dados = lerDados(r->tipo, r->qtd, r->caso);

    clock_t inicio3, fim3;

    inicio3 = clock();
    libera_ArvAVL(r, avl);
    fim3 = clock();

    r->tempo_esvaziar = (double)((fim3 - inicio3) / CLOCKS_PER_SEC);

    return true;
}

bool computarDadosAbp(Registro* r, FILE* arq) {
    ArvAVL* abp = cria_ArvBin();

    clock_t inicio, fim;
    inicio = clock();

    carregaArvoreABP(r, abp, arq);

    fim = clock();
    r->tempo_carregar = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // // r->altura = altura_No(((No*)abp));

    inicio = clock();
    for (int i = 0; i < 30; i++) {
        busca_ArvBin(abp, rand() % r->qtd);
    }
    fim = clock();
    r->tempo_consultar = (double)((fim - inicio) / CLOCKS_PER_SEC);

    // int* dados = lerDados(r->tipo, r->qtd, r->caso);

    // inicio = clock();
    // for (int i = 0; i < r->qtd; i++) {
    //     removeNoAvl(r, avl, dados[i]);
    // }
    // fim = clock();

    // r->tempo_esvaziar = (double)((fim - inicio) / CLOCKS_PER_SEC) / r->qtd;

    return true;
}

// Função responsável chamar o algoritmo de ordenação que le é passado
bool realizarOrdenacao(char tipo, char metodo, int tam, int casos_teste) {

    bool salvarRegistro(Registro);

    Registro r;
    r.tipo = tipo;
    r.qtd = tam;

    for (int j = 0; j < casos_teste; j++) {
        FILE* arq = abrirArquivoDados(tipo, tam, true, j);

        r.rot_carregar = 0;
        r.rot_esvaziar = 0;
        r.tempo_carregar = 0;
        r.tempo_consultar = 0;
        r.tempo_esvaziar = 0;
        r.caso = j;
        r.altura = 0;

        if (arq == NULL) {
            return false;
        }

        switch (metodo) {
        case 'v':
            r.metodo = AVL;
            computarDadosAVL(&r, arq);
            break;
        case 'b':
            r.metodo = BINARIA;
            computarDadosAbp(&r, arq);
            break;
        default:
            printf("Metodo %c não existe!\n", metodo);
            return false;
        }

        if (!salvarRegistro(r)) {
            printf("Erro ao escrever resultado\n");
            return false;
        }
    }

    return true;
}

// Função responsável por gerar o arquivo ou limpar caso já exista e salvar o header
bool criarArquivoResultado(char* metodo) {
    char path[40] = "";

    sprintf(path, "%s_%s.csv", RESULTADO_TXT, metodo);

    FILE* arquivo = fopen(path, "w+");
    if (arquivo == NULL)
        return false;

    if (fprintf(arquivo, "tipo, qtd, caso, tempo_carregar, tempo_consultar, tempo_esvaziar, rot_carregar, rot_esvaziar, altura\n") < 0) {
        printf("Erro ao criar arquivo de resultado\n");
        return false;
    }

    fclose(arquivo);

    return true;
}

// Função responsável por salvar o registro da execução no arquivo de resultado
bool salvarRegistro(Registro r) {
    char path[40] = "";

    sprintf(path, "%s_%s.csv", RESULTADO_TXT, r.metodo);

    FILE* arquivo = fopen(path, "a+");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de resultado %s.\n", path);
        return false;
    }

    if (fprintf(arquivo, "%c,%d,%d,%lf,%lf,%lf,%ld,%ld,%d\n", r.tipo, r.qtd, r.caso, r.tempo_carregar, r.tempo_consultar, r.tempo_esvaziar, r.rot_carregar, r.rot_esvaziar, r.altura) < 0) {
        printf("Erro ao salvar registro de resultado %s.\n", path);
        return false;
    }

    fclose(arquivo);

    return true;
}
