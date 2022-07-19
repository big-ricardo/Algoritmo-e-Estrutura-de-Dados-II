#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "rb.h"
#include "converte.h"

/*
  Luis Ricardo Albano Santos - 2021031844
  Matheus Martins Batista 2019005687
*/

int main() {

    char nomeArquivo[100];  //nome do arquivo de entrada
    int opcao;           //opcao de menu
    btree* btree;       //arvore 2-3-4
    rb* rb = NULL;     //arvore rubro negra

    btree = criaArvoreBt(4); //cria arvore 2-3-4

    //le o nome do arquivo de entrada
    printf("Insira o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    //Chama a função para ler o arquivo de entrada e inserir na arvore 2-3-4
    manipulaBTree(btree, nomeArquivo, 'i');

    //Chama a função para imprimir a arvore 2-3-4
    printf("\n ----Arvore 2-3-4----\n");
    imprimeArvore((retornaRaiz(btree)), 0);


    // Loop para o menu
    do {
        if (rb == NULL) {   //se a arvore rubro negra for nula exibe o menu da arvore 2-3-4

            // Exibe as opcoes de menu
            printf("\n---------Menu Btree---------\n");
            printf("1 - Inserir elemento na arvore 2-3-4\n");
            printf("2 - Remover elemento na arvore 2-3-4\n");
            printf("3 - Imprimir arvore 2-3-4\n");
            printf("4 - Converter em uma arvore rubro-negra\n");
            printf("5 - Sair\n");
            printf("----------------------\n");

            // Le a opcao do menu
            printf("Insira a opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                printf("Insira o elemento: "); //le o elemento a ser inserido
                scanf("%d", &opcao);
                insereElemento(btree, opcao);   //insere o elemento na arvore 2-3-4
                break;
            case 2:
                printf("Insira o elemento: ");  //le o elemento a ser removido
                scanf("%d", &opcao);
                removeElemento(btree, opcao);   //remove o elemento da arvore 2-3-4
                break;
            case 3:
                printf("\n --Arvore 2-3-4--\n");    //imprime a arvore 2-3-4
                imprimeArvore((retornaRaiz(btree)), 0);
                printf("\n");
                break;
            case 4:
                rb = converte(btree);   //converte a arvore 2-3-4 para uma arvore rubro-negra
                break;
            case 5:
                opcao = 0;  //sai do loop
                break;
            default:
                printf("Opcao invalida\n"); //opcao invalida
                break;
            }
        }
        else {  //se a arvore rubro negra nao for nula exibe o menu da arvore rubro-negra

            // Exibe as opcoes de menu
            printf("\n---------Menu Rubro-Negra---------\n");
            printf("1 - Inserir elemento na arvore rubro-negra\n");
            printf("2 - Remover elemento na arvore rubro-negra\n");
            printf("3 - Imprimir arvore rubro-negra\n");
            printf("4 - Sair\n");
            printf("----------------------\n");

            // Le a opcao do menu
            printf("Insira a opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                printf("Insira o elemento: ");  //le o elemento a ser inserido
                scanf("%d", &opcao);
                insereNo(rb, opcao);    //insere o elemento na arvore rubro-negra
                break;
            case 2:
                printf("Insira o elemento: ");  //le o elemento a ser removido
                scanf("%d", &opcao);
                removeNo(rb, opcao);    //remove o elemento da arvore rubro-negra
                break;
            case 3:
                printf("\n ----Arvore rubro-negra----\n");  //imprime a arvore rubro-negra
                percorre(getRaiz(rb));
                printf("\n");
                break;
            case 4:
                opcao = 0;  //sai do loop
                break;
            default:
                printf("Opcao invalida\n"); //opcao invalida
                break;
            }
        }
    } while (opcao != 0);   //enquanto a opcao for diferente de 0 continua no menu

    return 0;
}